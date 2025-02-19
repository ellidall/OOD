import {ShapeType} from '../../types/shapes'
import {BaseShape} from './BaseShape'

class Rectangle extends BaseShape {
	override getType(): ShapeType {
		return 'rectangle'
	}
}

export {
	Rectangle,
}