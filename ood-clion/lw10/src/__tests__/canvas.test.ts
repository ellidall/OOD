// eslint-disable-next-line import/no-extraneous-dependencies
import {describe, expect} from '@jest/globals'
import {CanvasModel} from '../models/CanvasModel'

describe('CanvasModel', () => {
	let canvas: CanvasModel

	beforeEach(() => {
		canvas = new CanvasModel()
	})

	it('should add an art object and notify observers', () => {
		const observer = jest.fn()
		canvas.addObserver(observer)

		canvas.addArtObject('rectangle')
		const shapes = Array.from(canvas.getShapeIdToShapeMap().values())

		expect(shapes).toHaveLength(1)
		expect(shapes[0]?.getType()).toBe('rectangle')
		expect(observer).toHaveBeenCalledWith(expect.any(String), 'create')
	})

	it('should undo adding an art object', () => {
		canvas.addArtObject('ellipse')
		const shapeIdsBeforeUndo = Array.from(canvas.getShapeIdToShapeMap().keys())

		canvas.undo()
		const shapeIdsAfterUndo = Array.from(canvas.getShapeIdToShapeMap().keys())

		expect(shapeIdsBeforeUndo).toHaveLength(1)
		expect(shapeIdsAfterUndo).toHaveLength(0)
		expect(canvas.canUndo()).toBe(false)
	})

	it('should add an image and notify observers', () => {
		const observer = jest.fn()
		canvas.addObserver(observer)

		canvas.addImage('imageData')
		const shapes = Array.from(canvas.getShapeIdToShapeMap().values())

		expect(shapes).toHaveLength(1)
		expect(shapes[0]?.getType()).toBe('image')
		expect(observer).toHaveBeenCalledWith(expect.any(String), 'create')
	})

	it('should undo adding an image', () => {
		canvas.addImage('imageData')
		const shapeIdsBeforeUndo = Array.from(canvas.getShapeIdToShapeMap().keys())

		canvas.undo()
		const shapeIdsAfterUndo = Array.from(canvas.getShapeIdToShapeMap().keys())

		expect(shapeIdsBeforeUndo).toHaveLength(1)
		expect(shapeIdsAfterUndo).toHaveLength(0)
		expect(canvas.canUndo()).toBe(false)
	})

	it('should remove a shape and notify observers', () => {
		const observer = jest.fn()
		canvas.addObserver(observer)

		canvas.addArtObject('triangle')
		const shapeId = Array.from(canvas.getShapeIdToShapeMap().keys())[0]

		canvas.removeShape(shapeId ?? '')
		const shapes = Array.from(canvas.getShapeIdToShapeMap().keys())

		expect(shapes).toHaveLength(0)
		expect(observer).toHaveBeenCalledWith(shapeId, 'delete')
	})

	it('should undo removing a shape', () => {
		canvas.addArtObject('triangle')
		const shapeId = Array.from(canvas.getShapeIdToShapeMap().keys())[0]
		canvas.removeShape(shapeId ?? '')

		canvas.undo()
		const shapes = Array.from(canvas.getShapeIdToShapeMap().values())

		expect(shapes).toHaveLength(1)
		expect(shapes[0]?.getType()).toBe('triangle')
	})

	it('should update a shape size and position, then undo', () => {
		canvas.addArtObject('rectangle')
		const shapeId = Array.from(canvas.getShapeIdToShapeMap().keys())[0]

		canvas.updateShapeSizeAndPosition(shapeId ?? '', {
			size: {width: 200, height: 150},
			position: {x: 50, y: 50},
		})

		const updatedShape = canvas.getShape(shapeId ?? '')
		expect(updatedShape.getSize()).toEqual({width: 200, height: 150})
		expect(updatedShape.getPosition()).toEqual({x: 50, y: 50})

		canvas.undo()

		const revertedShape = canvas.getShape(shapeId ?? '')
		expect(revertedShape.getSize()).toEqual({width: 100, height: 100})
		expect(revertedShape.getPosition()).toEqual({x: 0, y: 0})
	})

	it('should serialize and load canvas correctly', () => {
		canvas.addArtObject('ellipse')
		const shapeId = Array.from(canvas.getShapeIdToShapeMap().keys())[0]

		const json = canvas.serializeCanvasToJson()
		canvas.addArtObject('triangle')
		canvas.loadCanvasFromJson(json)

		const shapes = Array.from(canvas.getShapeIdToShapeMap().keys())
		expect(shapes).toHaveLength(1)
		expect(canvas.getShape(shapeId ?? '').getType()).toBe('ellipse')
	})

	it('should validate canvas loading', () => {
		const invalidJson = '{"invalid": "data"}'
		expect(() => canvas.loadCanvasFromJson(invalidJson)).toThrow('Invalid canvas data format')
	})

	it('should add and remove observers', () => {
		const observer = jest.fn()
		canvas.addObserver(observer)

		canvas.addArtObject('rectangle')
		expect(observer).toHaveBeenCalled()

		canvas.removeObserver(observer)
		observer.mockClear()
		canvas.addArtObject('triangle')

		expect(observer).not.toHaveBeenCalled()
	})

	it('should retrieve canvas size', () => {
		const size = canvas.getCanvasSize()
		expect(size).toEqual({width: 1200, height: 680})
	})

	it('try to get non existent shape', () => {
		expect(() => canvas.getShape('1')).toThrow('Shape with id 1 not found')
	})

	it('should remove an image and notify observers, then undo', () => {
		const observer = jest.fn()
		canvas.addObserver(observer)

		canvas.addImage('imageData')
		const shapeId = Array.from(canvas.getShapeIdToShapeMap().keys())[0]

		canvas.removeShape(shapeId ?? '')
		expect(Array.from(canvas.getShapeIdToShapeMap().keys())).toHaveLength(0)
		expect(observer).toHaveBeenCalledWith(shapeId, 'delete')

		canvas.undo()
		const shapes = Array.from(canvas.getShapeIdToShapeMap().values())
		expect(shapes).toHaveLength(1)
		expect(shapes[0]?.getType()).toBe('image')
	})

	it('should remove the oldest command when history exceeds 10 commands', () => {
		for (let i = 0; i < 11; i++) {
			canvas.addArtObject(`rectangle`)
		}

		const shapeIds = Array.from(canvas.getShapeIdToShapeMap().keys())
		expect(shapeIds).toHaveLength(11)

		for (let i = 0; i < 11; i++) {
			canvas.undo()
		}

		const remainingShapes = Array.from(canvas.getShapeIdToShapeMap().values())
		expect(remainingShapes).toHaveLength(1)
		expect(remainingShapes[0]?.getType()).toBe('rectangle')
	})
})
