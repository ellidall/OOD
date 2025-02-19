import {ArtObjectType, ShapePosition, ShapeSize} from '../types/shapes'
import {
	InsertArtObjectCommand,
	InsertImageObjectCommand,
	RemoveShapeCommand,
	UpdateShapeSizeAndPositionCommand,
} from './Command/commands'
import {History} from './history/history'
import {BaseShape, IShape} from './Shape/BaseShape'
import {ShapeFactory} from './ShapeFactory'

type ChangeEvent = 'create' | 'update' | 'delete'

type ShapeChangeObserver = (shapeId: string, event: ChangeEvent) => void

type ICanvasReadModel = {
	getShape: (shapeId: string) => IShape,
	getCanvasSize: () => ShapeSize,
	getShapeIdToShapeMap: () => Map<string, IShape>,
	serializeCanvasToJson: () => string,
}

type ICanvasModel = ICanvasReadModel & {
	addArtObject: (type: ArtObjectType) => void,
	addImage: (data: string) => void,
	removeShape: (shapeId: string) => void,
	undo: () => void,
	redo: () => void,
	canUndo: () => boolean,
	canRedo: () => boolean,
	loadCanvasFromJson: (jsonString: string) => void,
	addObserver: (onShapeChange: ShapeChangeObserver) => void,
	removeObserver: (onShapeChange: ShapeChangeObserver) => void,
	updateShapeSizeAndPosition: (shapeId: string, changes: {size?: ShapeSize, position?: ShapePosition}) => void,
}

class CanvasModel implements ICanvasModel {
	private canvasSize: ShapeSize = {width: 1488, height: 680}
	private shapes: Map<string, BaseShape> = new Map()
	private shapeChangeObservers: ShapeChangeObserver[] = []
	private history: History = new History()

	addArtObject(type: ArtObjectType): void {
		this.history.addAndExecuteCommand(
			new InsertArtObjectCommand(type, this),
		)
	}

	addImage(data: string) {
		this.history.addAndExecuteCommand(
			new InsertImageObjectCommand(data, this),
		)
	}

	removeShape(shapeId: string) {
		this.history.addAndExecuteCommand(
			new RemoveShapeCommand(shapeId, this),
		)
	}

	undo() {
		if (this.history.canUndo()) {
			this.history.undo()
		}
	}

	redo() {
		if (this.history.canRedo()) {
			this.history.redo()
		}
	}

	canUndo = () => this.history.canUndo()

	canRedo = () => this.history.canRedo()

	updateShapeSizeAndPosition(shapeId: string, changes: {size?: ShapeSize, position?: ShapePosition}) {
		this.history.addAndExecuteCommand(new UpdateShapeSizeAndPositionCommand(
			shapeId,
			this,
			changes.size,
			changes.position,
		))
	}

	loadCanvasFromJson(jsonString: string) {
		this.history.clear()
		this._loadCanvasFromJson(jsonString)
	}

	getShape(shapeId: string): BaseShape {
		const shape = this.shapes.get(shapeId)
		if (!shape) {
			throw new Error(`Shape with id ${shapeId} not found`)
		}
		return shape
	}

	getShapeIdToShapeMap(): Map<string, BaseShape> {
		return new Map(this.shapes)
	}

	getCanvasSize(): ShapeSize {
		return this.canvasSize
	}

	serializeCanvasToJson(): string {
		const shapes = Array.from(this.getShapeIdToShapeMap().entries()).map(([shapeId, shape]) => ({
			shapeId,
			type: shape.getType(),
			size: shape.getSize(),
			position: shape.getPosition(),
			data: (shape as any).getData?.() || undefined,
		}))

		const canvasData = {
			canvasSize: this.getCanvasSize(),
			shapes,
		}

		return JSON.stringify(canvasData)
	}

	addObserver(onShapeChange: ShapeChangeObserver) {
		this.shapeChangeObservers.push(onShapeChange)
	}

	removeObserver(onShapeChange: ShapeChangeObserver) {
		const index = this.shapeChangeObservers.indexOf(onShapeChange)
		if (index !== -1) {
			this.shapeChangeObservers.splice(index, 1)
		}
	}

	_removeShape(shapeId: string) {
		if (this.shapes.has(shapeId)) {
			this.shapes.delete(shapeId)
			this._notifyObservers(shapeId, 'delete')
		}
	}

	_addShape(shape: BaseShape, shapeId?: string): string {
		const id = shapeId ?? this._generateUniqueId()
		this.shapes.set(id, shape)
		this._notifyObservers(id, 'create')
		this.shapes = new Map([...this.shapes.entries()].sort(([keyA], [keyB]) => keyA.localeCompare(keyB)))
		return id
	}

	_updateShapeSizeAndPosition(shapeId: string, changes: {
		size?: ShapeSize,
		position?: ShapePosition,
	}) {
		const shape = this.getShape(shapeId)
		if (!shape) {
			throw new Error(`Shape with id ${shapeId} not found`)
		}

		if (!changes.size && !changes.position) {
			return
		}

		const newSize = changes.size ?? shape.getSize()
		const newPosition = changes.position ?? shape.getPosition()

		if (newPosition.x < 0 || newPosition.y < 0) {
			throw new Error(`Invalid shape position. X and y must not be less than 0`)
		}
		if (newSize.width <= 0 || newSize.height <= 0) {
			throw new Error(`Invalid shape size. Width and height must be greater than 0`)
		}
		if ((newSize.width + newPosition.x) > this.canvasSize.width || (newSize.height + newPosition.y) > this.canvasSize.height) {
			throw new Error(`Shape size exceeds canvas boundaries`)
		}

		shape.move(newPosition)
		shape.resize(newSize)
		this._notifyObservers(shapeId, 'update')
	}

	_loadCanvasFromJson(jsonString: string) {
		const jsonData = JSON.parse(jsonString)

		if (this._validateCanvasDataJson(jsonData)) {
			const currentShapes = Array.from(this.getShapeIdToShapeMap().keys())
			currentShapes.forEach(shapeId => this._removeShape(shapeId))
			this.canvasSize = jsonData.canvasSize
			jsonData.shapes.forEach((shape: any) => {
				const newShape = ShapeFactory.constructShape(
					shape.type,
					shape.data,
				)
				newShape.resize(shape.size)
				newShape.move(shape.position)
				this._addShape(newShape, shape.shapeId)
			})
		}
		else {
			throw new Error('Invalid canvas data format')
		}
	}

	private _validateShapeJson(shape: any): boolean {
		return (
			typeof shape.shapeId === 'string'
			&& typeof shape.type === 'string'
			&& typeof shape.size === 'object'
			&& typeof shape.size.width === 'number'
			&& typeof shape.size.height === 'number'
			&& typeof shape.position === 'object'
			&& typeof shape.position.x === 'number'
			&& typeof shape.position.y === 'number'
			&& (shape.data === undefined || typeof shape.data === 'string')
		)
	}

	private _validateCanvasDataJson(data: any): boolean {
		return (
			typeof data.canvasSize === 'object'
			&& typeof data.canvasSize.width === 'number'
			&& typeof data.canvasSize.height === 'number'
			&& Array.isArray(data.shapes)
			&& data.shapes.every((shape: any) => this._validateShapeJson(shape))
		)
	}

	private _notifyObservers(shapeId: string, event: ChangeEvent) {
		for (const observer of this.shapeChangeObservers) {
			observer(shapeId, event)
		}
	}

	private _generateUniqueId(): string {
		const timestamp = Date.now().toString(36)
		const randomPart = Math.floor(Math.random() * 1e9).toString(36)
		return `${timestamp}-${randomPart}`
	}
}

export {
	CanvasModel,
}

export type {
	ICanvasModel,
	ICanvasReadModel,
	ShapeChangeObserver,
	ChangeEvent,
}