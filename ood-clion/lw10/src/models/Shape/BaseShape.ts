import {ShapePosition, ShapeSize, ShapeType} from '../../types/shapes'

type IShape = {
	getPosition: () => ShapePosition,
	getSize: () => ShapeSize,
	getType: () => ShapeType,
}

abstract class BaseShape implements IShape {
	private position: ShapePosition = {x: 0, y: 0}
	private size: ShapeSize

	constructor(size: ShapeSize) {
		this.size = size
	}

	getPosition(): ShapePosition {
		return this.position
	}

	getSize(): ShapeSize {
		return this.size
	}

	resize(size: ShapeSize): void {
		this.size = size
	}

	move(position: ShapePosition): void {
		this.position = position
	}

	abstract getType(): ShapeType
}

export {
	BaseShape,
}

export type {
	IShape,
}
