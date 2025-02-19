import {ICanvasModel} from '../models/CanvasModel'
import {ShapePosition, ShapeSize} from '../types/shapes'

class ShapeController {
	private readonly minSize = 20

	constructor(private model: ICanvasModel) {
	}

	handleMove(
		shapeId: string,
		initialPosition: ShapePosition,
		deltaX: number,
		deltaY: number,
	) {
		const canvasSize = this.model.getCanvasSize()
		const shapeSize = this.model.getShape(shapeId).getSize()

		const clamp = (value: number, min: number, max: number): number => Math.max(min, Math.min(max, value))

		let newPosX = initialPosition.x + deltaX
		let newPosY = initialPosition.y + deltaY

		newPosX = clamp(newPosX, 0, canvasSize.width - shapeSize.width)
		newPosY = clamp(newPosY, 0, canvasSize.height - shapeSize.height)

		this.updateShapeSizeAndPosition(shapeId, {
			position: {
				x: newPosX,
				y: newPosY,
			},
		})
	}

	handleResize(
		shapeId: string,
		initial: {width: number, height: number, x: number, y: number},
		delta: ShapePosition,
		resizeCorner: string,
	) {
		const canvasSize = this.model.getCanvasSize()
		const {x: deltaX, y: deltaY} = delta
		const topResize = (oldHeight: number, oldPosY: number): [number, number] => {
			let newHeight = oldHeight - deltaY
			let newY = oldPosY + deltaY
			if (newY < 0) {
				newHeight += newY
				newY = 0
			}
			if (newHeight < this.minSize) {
				newHeight = this.minSize
				newY = oldPosY + oldHeight - this.minSize
			}
			return [newHeight, newY]
		}

		const bottomResize = (oldHeight: number, oldPosY: number): [number, number] => {
			const newHeight = oldHeight + deltaY
			const maxHeight = canvasSize.height - oldPosY
			return newHeight > maxHeight ? [maxHeight, oldPosY] : [Math.max(newHeight, this.minSize), oldPosY]
		}

		const leftResize = (oldWidth: number, oldPosX: number): [number, number] => {
			let newWidth = oldWidth - deltaX
			let newX = oldPosX + deltaX
			if (newX < 0) {
				newWidth += newX
				newX = 0
			}
			if (newWidth < this.minSize) {
				newWidth = this.minSize
				newX = oldPosX + oldWidth - this.minSize
			}
			return [newWidth, newX]
		}

		const rightResize = (oldWidth: number, oldPosX: number): [number, number] => {
			const newWidth = oldWidth + deltaX
			const maxWidth = canvasSize.width - oldPosX
			return newWidth > maxWidth ? [maxWidth, oldPosX] : [Math.max(newWidth, this.minSize), oldPosX]
		}

		let {width, height, x, y} = initial

		switch (resizeCorner) {
			case 'top-left':
				[height, y] = topResize(height, y);
				[width, x] = leftResize(width, x)
				break
			case 'top-right':
				[height, y] = topResize(height, y);
				[width, x] = rightResize(width, x)
				break
			case 'bottom-left':
				[height, y] = bottomResize(height, y);
				[width, x] = leftResize(width, x)
				break
			case 'bottom-right':
				[height, y] = bottomResize(height, y);
				[width, x] = rightResize(width, x)
				break
			default:
				return
		}

		this.updateShapeSizeAndPosition(shapeId, {
			size: {width, height},
			position: {x, y},
		})
	}

	private updateShapeSizeAndPosition(shapeId: string, changes: {size?: ShapeSize, position?: ShapePosition}) {
		this.model.updateShapeSizeAndPosition(shapeId, changes)
	}
}

export {ShapeController}
