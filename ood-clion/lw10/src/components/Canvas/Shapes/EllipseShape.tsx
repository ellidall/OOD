import {Component} from 'react'

class EllipseShape extends Component {
	private color = '#d75050'

	override render() {
		return (
			<svg width="100%" height="100%" viewBox="0 0 100 100" preserveAspectRatio="none">
				<ellipse cx="50" cy="50" rx="50" ry="50" fill={this.color} />
			</svg>
		)
	}
}

export {
	EllipseShape,
}
