import {ShapeController} from 'controllers/ShapeController'
import React, {Component, createRef, ReactElement} from 'react'
import {ShapePosition, ShapeSize} from 'types/shapes'

type InteractiveShapeProps = {
	isSelected: boolean,
	setIsSelected: (selected: boolean) => void,
	shapeSize: ShapeSize,
	shapePosition: ShapePosition,
	shape: ReactElement,
	shapeId: string,
	shapeController: ShapeController,
	canvasSize: ShapeSize,
	canvasId: string,
}

class InteractiveShape extends Component<InteractiveShapeProps> {
	private isDragging = false
	private dragStartX = 0
	private dragStartY = 0
	private resizeCorner = ''

	private isResizing = false
	private resizeStartX = 0
	private resizeStartY = 0
	private initialWidth = 0
	private initialHeight = 0
	private initialX = 0
	private initialY = 0

	private resizeShapeColor = '#b91def'

	private shapeRef = createRef<HTMLDivElement>()

	handleMouseDown = (e: React.MouseEvent) => {
		e.stopPropagation()
		this.props.setIsSelected(true)
		this.isDragging = true
		this.dragStartX = e.clientX
		this.dragStartY = e.clientY

		window.addEventListener('mousemove', this.handleMouseMove)
		window.addEventListener('mouseup', this.handleMouseUp)
	}

	handleMouseMove = (e: MouseEvent) => {
		const deltaX = e.clientX - (this.isDragging ? this.dragStartX : this.resizeStartX)
		const deltaY = e.clientY - (this.isDragging ? this.dragStartY : this.resizeStartY)

		if (this.isDragging) {
			this.props.shapeController.handleMove(
				this.props.shapeId,
				this.props.shapePosition,
				deltaX,
				deltaY,
			)
			this.dragStartX = e.clientX
			this.dragStartY = e.clientY
		}

		if (this.isResizing) {
			this.props.shapeController.handleResize(
				this.props.shapeId,
				{
					width: this.initialWidth,
					height: this.initialHeight,
					x: this.initialX,
					y: this.initialY,
				},
				{
					x: deltaX,
					y: deltaY,
				},
				this.resizeCorner,
			)
		}
	}

	handleMouseUp = () => {
		this.isDragging = false
		this.isResizing = false
		window.removeEventListener('mousemove', this.handleMouseMove)
		window.removeEventListener('mouseup', this.handleMouseUp)
	}

	handleResizeMouseDown = (e: React.MouseEvent, corner: string) => {
		e.stopPropagation()
		this.isResizing = true
		this.resizeCorner = corner
		this.resizeStartX = e.clientX
		this.resizeStartY = e.clientY
		this.initialWidth = this.props.shapeSize.width
		this.initialHeight = this.props.shapeSize.height
		this.initialX = this.props.shapePosition.x
		this.initialY = this.props.shapePosition.y

		window.addEventListener('mousemove', this.handleMouseMove)
		window.addEventListener('mouseup', this.handleMouseUp)
	}

	renderResizeHandles() {
		const {isSelected} = this.props
		if (!isSelected) {
			return null
		}

		return (
			<>
				<div
					style={{
						position: 'absolute',
						top: -5,
						left: -5,
						width: 10,
						height: 10,
						backgroundColor: this.resizeShapeColor,
						cursor: 'nw-resize',
					}}
					onMouseDown={e => this.handleResizeMouseDown(e, 'top-left')}
				/>
				<div
					style={{
						position: 'absolute',
						top: -5,
						right: -5,
						width: 10,
						height: 10,
						backgroundColor: this.resizeShapeColor,
						cursor: 'ne-resize',
					}}
					onMouseDown={e => this.handleResizeMouseDown(e, 'top-right')}
				/>
				<div
					style={{
						position: 'absolute',
						bottom: -5,
						left: -5,
						width: 10,
						height: 10,
						backgroundColor: this.resizeShapeColor,
						cursor: 'sw-resize',
					}}
					onMouseDown={e => this.handleResizeMouseDown(e, 'bottom-left')}
				/>
				<div
					style={{
						position: 'absolute',
						bottom: -5,
						right: -5,
						width: 10,
						height: 10,
						backgroundColor: this.resizeShapeColor,
						cursor: 'se-resize',
					}}
					onMouseDown={e => this.handleResizeMouseDown(e, 'bottom-right')}
				/>
			</>
		)
	}

	handleClickOutside = (event: MouseEvent | TouchEvent) => {
		if (this.shapeRef.current
			&& !this.shapeRef.current.contains(event.target as Node)
			&& document.getElementById(this.props.canvasId)?.contains(event.target as Node)
		) {
			this.props.setIsSelected(false)
		}
	}

	override render() {
		const {isSelected, shapeSize, shapePosition, shape} = this.props

		return (
			<div
				style={{
					position: 'absolute',
					top: shapePosition.y,
					left: shapePosition.x,
					width: shapeSize.width,
					height: shapeSize.height,
					outline: isSelected ? '2px solid #000000' : 'none',
					cursor: isSelected ? 'move' : 'default',
				}}
				onMouseDown={this.handleMouseDown}
				ref={this.shapeRef}
			>
				{shape}
				{this.renderResizeHandles()}
			</div>
		)
	}

	override componentDidMount() {
		document.addEventListener('mousedown', this.handleClickOutside)
	}

	override componentWillUnmount() {
		document.removeEventListener('mousedown', this.handleClickOutside)
	}
}

export {
	InteractiveShape,
}
