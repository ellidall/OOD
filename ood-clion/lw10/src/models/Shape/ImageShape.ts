import {ShapeSize, ShapeType} from 'types/shapes'
import {BaseShape} from './BaseShape'

class ImageShape extends BaseShape {
	data: string

	constructor(size: ShapeSize, data: string) {
		super(size)
		this.data = data
	}

	override getType(): ShapeType {
		return 'image'
	}

	getData = () => this.data
}

export {
	ImageShape,
}