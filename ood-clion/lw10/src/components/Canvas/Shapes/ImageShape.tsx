import {Component} from 'react'

type ImageShapeProps = {
	src: string,
}

class ImageShape extends Component<ImageShapeProps> {
	override render() {
		const {src} = this.props
		return (
			<svg width="100%" height="100%" viewBox="0 0 100 100" preserveAspectRatio="none">
				<image href={src} width="100%" height="100%" />
			</svg>
		)
	}
}

export {
	ImageShape,
}