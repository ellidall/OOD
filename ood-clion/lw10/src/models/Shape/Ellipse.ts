import {ShapeType} from '../../types/shapes'
import {BaseShape} from './BaseShape'

class Ellipse extends BaseShape {
	override getType(): ShapeType {
		return 'ellipse'
	}
}

export {
	Ellipse,
}