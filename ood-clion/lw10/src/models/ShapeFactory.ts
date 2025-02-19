import {ShapeSize, ShapeType} from '../types/shapes'
import {BaseShape} from './Shape/BaseShape'
import {Ellipse} from './Shape/Ellipse'
import {ImageShape} from './Shape/ImageShape'
import {Rectangle} from './Shape/Rectangle'
import {Triangle} from './Shape/Triangle'

class ShapeFactory {
	private static defaultSize: ShapeSize = {width: 100, height: 100}

	static constructShape(type: ShapeType, data?: string): BaseShape {
		switch (type) {
			case 'ellipse':
				return new Ellipse(this.defaultSize)
			case 'rectangle':
				return new Rectangle(this.defaultSize)
			case 'triangle':
				return new Triangle(this.defaultSize)
			case 'image':
				return new ImageShape(this.defaultSize, data ?? '')
		}
	}
}

export {
	ShapeFactory,
}