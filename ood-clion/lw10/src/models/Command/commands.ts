import {ArtObjectType, ShapePosition, ShapeSize} from '../../types/shapes'
import {CanvasModel} from '../CanvasModel'
import {BaseShape} from '../Shape/BaseShape'
import {ShapeFactory} from '../ShapeFactory'
import {ImageLocalStorage} from '../Storage/ImageLocalStorage'

type ICommand = {
	execute: () => void,
	unexecute: () => void,
	destroy: () => void,
	canMergeWith: (command: ICommand) => boolean,
	mergeWith: (command: ICommand) => void,
}

abstract class AbstractCommand implements ICommand {
	private executed = false

	protected constructor() {}

	execute(): void {
		if (!this.executed) {
			this.doExecute()
			this.executed = true
		}
	}

	unexecute(): void {
		if (this.executed) {
			this.doUnexecute()
			this.executed = false
		}
	}

	canMergeWith(_: ICommand) {
		return false
	}

	mergeWith(_: ICommand) {
		throw new Error('Not implemented')
	}

	abstract destroy(): void

	protected abstract doExecute(): void

	protected abstract doUnexecute(): void
}

class InsertArtObjectCommand extends AbstractCommand {
	private insertedShapeId?: string

	constructor(
		private type: ArtObjectType,
		private canvasModel: CanvasModel,
	) {
		super()
	}

	doExecute() {
		this.insertedShapeId = this.canvasModel._addShape(ShapeFactory.constructShape(this.type), this.insertedShapeId)
	}

	doUnexecute() {
		if (this.insertedShapeId) {
			this.canvasModel._removeShape(this.insertedShapeId)
		}
	}

	destroy() {
	}
}

class InsertImageObjectCommand extends AbstractCommand {
	private insertedShapeId?: string
	private shouldDelete = false
	private data?: string

	constructor(
		data: string,
		private canvasModel: CanvasModel,
	) {
		super()
		this.data = data
	}

	doExecute() {
		if (this.insertedShapeId) {
			this.data = ImageLocalStorage.getImageData(this.insertedShapeId)
			if (this.data) {
				ImageLocalStorage.removeImage(this.insertedShapeId)
			}
		}
		this.insertedShapeId = this.canvasModel._addShape(ShapeFactory.constructShape('image', this.data), this.insertedShapeId)
		ImageLocalStorage.addImage(this.insertedShapeId, this.data ?? '')
		this.shouldDelete = false
	}

	doUnexecute() {
		if (this.insertedShapeId) {
			this.canvasModel._removeShape(this.insertedShapeId)
		}
		this.shouldDelete = true
	}

	destroy() {
		if (this.shouldDelete && this.insertedShapeId) {
			ImageLocalStorage.removeImage(this.insertedShapeId)
		}
	}
}

class UpdateShapeSizeAndPositionCommand extends AbstractCommand {
	private oldSize?: ShapeSize
	private oldPosition?: ShapePosition

	constructor(
		private shapeId: string,
		private canvasModel: CanvasModel,
		private newSize?: ShapeSize,
		private newPosition?: ShapePosition,
	) {
		super()
	}

	doExecute() {
		const shape = this.canvasModel.getShape(this.shapeId)
		this.oldSize = shape.getSize()
		this.oldPosition = shape.getPosition()

		this.canvasModel._updateShapeSizeAndPosition(
			this.shapeId,
			{
				size: this.newSize,
				position: this.newPosition,
			},
		)
	}

	doUnexecute() {
		this.canvasModel._updateShapeSizeAndPosition(
			this.shapeId,
			{
				size: this.oldSize,
				position: this.oldPosition,
			},
		)
	}

	destroy() {
	}

	override canMergeWith(command: ICommand): boolean {
		if (command instanceof UpdateShapeSizeAndPositionCommand) {
			return this.shapeId === command.shapeId
		}
		return false
	}

	override mergeWith(command: ICommand): void {
		if (command instanceof UpdateShapeSizeAndPositionCommand) {
			this.newSize = command.newSize || this.newSize
			this.newPosition = command.newPosition || this.newPosition
		}
		else {
			throw new Error('Cannot merge with incompatible command')
		}
	}
}

class RemoveShapeCommand extends AbstractCommand {
	private shape?: BaseShape

	constructor(
		private shapeId: string,
		private canvasModel: CanvasModel,
	) {
		super()
	}

	doExecute() {
		this.shape = this.canvasModel.getShape(this.shapeId)
		this.canvasModel._removeShape(this.shapeId)
	}

	doUnexecute() {
		if (this.shape) {
			this.canvasModel._addShape(this.shape, this.shapeId)
		}
	}

	destroy() {
	}
}

export type {
	ICommand,
}

export {
	AbstractCommand,
	InsertArtObjectCommand,
	InsertImageObjectCommand,
	UpdateShapeSizeAndPositionCommand,
	RemoveShapeCommand,
}