import {Component} from 'react'

class RectangleShape extends Component {
	private color = 'green'

	override render() {
		return (
			<svg width="100%" height="100%">
				<rect width="100%" height="100%" fill={this.color} />
			</svg>
		)
	}
}

export {
	RectangleShape,
}
