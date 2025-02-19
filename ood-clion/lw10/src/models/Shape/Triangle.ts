import {ShapeType} from 'types/shapes'
import {BaseShape} from './BaseShape'

class Triangle extends BaseShape {
	override getType(): ShapeType {
		return 'triangle'
	}
}

export {
	Triangle,
}