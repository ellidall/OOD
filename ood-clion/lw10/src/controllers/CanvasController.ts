import {ICanvasModel, ShapeChangeObserver} from '../models/CanvasModel'
import {ArtObjectType} from '../types/shapes'

class CanvasController {
	constructor(
		private model: ICanvasModel,
	) {
	}

	addArtObject(type: ArtObjectType) {
		this.model.addArtObject(type)
	}

	addImage(data: string) {
		this.model.addImage(data)
	}

	removeShape(shapeId: string) {
		this.model.removeShape(shapeId)
	}

	undo() {
		this.model.undo()
	}

	redo() {
		this.model.redo()
	}

	canUndo = () => this.model.canUndo()

	canRedo = () => this.model.canRedo()

	loadCanvasFromJson(jsonString: string) {
		this.model.loadCanvasFromJson(jsonString)
	}

	addObserver(onShapeChange: ShapeChangeObserver) {
		this.model.addObserver(onShapeChange)
	}

	removeObserver(onShapeChange: ShapeChangeObserver) {
		this.model.removeObserver(onShapeChange)
	}
}

export {
	CanvasController,
}