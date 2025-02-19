import {Component} from 'react'

class TriangleShape extends Component {
	private color = '#6ac45c'

	override render() {
		return (
			<svg width="100%" height="100%" viewBox="0 0 100 100" preserveAspectRatio="none">
				<polygon points="50,0 100,100 0,100" fill={this.color} />
			</svg>
		)
	}
}

export {
	TriangleShape,
}