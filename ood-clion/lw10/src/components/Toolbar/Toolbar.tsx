import React, {ChangeEvent, Component, CSSProperties} from 'react'
import {CanvasController} from '../../controllers/CanvasController'
import {ICanvasReadModel} from '../../models/CanvasModel'
import {ArtObjectType} from '../../types/shapes'
import {EllipseShape} from '../Canvas/Shapes/EllipseShape'
import {RectangleShape} from '../Canvas/Shapes/RectangleShape'
import {TriangleShape} from '../Canvas/Shapes/TriangleShape'

type ToolbarProps = {
	controller: CanvasController,
	canvasModel: ICanvasReadModel,
	selectedShapeId?: string,
	setSelectedShapeId: (shapeId?: string) => void,
	handleDeleteShape: (shapeId: string) => void,
}

class Toolbar extends Component<ToolbarProps> {
	private readonly controller: CanvasController
	private readonly canvasModel: ICanvasReadModel

	constructor(props: ToolbarProps) {
		super(props)
		this.canvasModel = this.props.canvasModel
		this.controller = props.controller
		this.controller.addObserver(() => this.observer())
	}

	observer() {
		this.forceUpdate()
	}

	override render() {
		return (
			<div style={{
				display: 'flex',
				gap: 10,
				height: 60,
				width: 1488,
				background: '#c39ee8',
				boxSizing: 'border-box',
				alignItems: 'center',
				justifyContent: 'center'
			}}>
				<JsonBlock
					controller={this.controller}
					model={this.canvasModel}
					onLoad={() => this.props.setSelectedShapeId(undefined)}
				/>
				<CreateBlock controller={this.controller} />
				<HistoryBlock
					controller={this.controller}
					selectedShapeId={this.props.selectedShapeId}
					handleDeleteShape={this.props.handleDeleteShape}
				/>
			</div>
		)
	}
}

const JsonBlock: React.FC<{
	controller: CanvasController,
	model: ICanvasReadModel,
	onLoad: () => void
}> = ({controller, model, onLoad}) => {
	const buttonStyle: CSSProperties = {
		display: 'flex',
		justifyContent: 'center',
		alignItems: 'center',
		borderRadius: 5,
		border: 'solid 2px #413737'
	}

	const handleSaveJson = (jsonData: string) => {
		const blob = new Blob([jsonData], {type: 'application/json'})
		const url = URL.createObjectURL(blob)
		const a = document.createElement('a')
		a.href = url
		a.download = 'Presentation.json'
		a.click()
		URL.revokeObjectURL(url)
		alert('Успешно сохранено')
	}

	const handleLoadJson = (event: React.ChangeEvent<HTMLInputElement>, controller: CanvasController) => {
		const fileInput = event.target
		const file = fileInput.files?.[0]

		if (file) {
			const reader = new FileReader()
			reader.onload = e => {
				try {
					const jsonString = e.target?.result as string
					controller.loadCanvasFromJson(jsonString)
				}
				catch (error) {
					alert(error)
				}
			}

			reader.readAsText(file)
		}
		onLoad()
	}

	return(
		<div style={{display: 'flex', gap: '10px', padding: '10px'}}>
			<button onClick={() => handleSaveJson(model.serializeCanvasToJson())} style={buttonStyle}>{'Save'}</button>
			<input
				id={'inputJson'}
				type={'file'}
				accept={'.json'}
				onChange={e => handleLoadJson(e, controller)}
				style={{display: 'none'}}
			/>
			<button style={buttonStyle}>
				<label htmlFor={'inputJson'}>
					{'Load'}
				</label>
			</button>
		</div>
	)
}

const CreateBlock = React.memo(({controller}: {controller: CanvasController}) => {
	const buttonStyle: CSSProperties = {
		width: 40,
		height: 40,
		display: 'flex',
		justifyContent: 'center',
		alignItems: 'center',
		borderRadius: 5,
		border: 'solid 2px #413737'
	}

	const handleImageUpload = (event: ChangeEvent<HTMLInputElement>) => {
		const file = event.target.files?.[0]
		if (!file) {
			return
		}

		const reader = new FileReader()
		reader.onload = e => {
			controller.addImage((e.target?.result ?? '') as string)
		}
		reader.readAsDataURL(file)
	}

	const renderIcon = (type: ArtObjectType): JSX.Element => {
		switch (type) {
			case 'rectangle':
				return <div style={{width: 16, height: 16}}><RectangleShape/></div>
			case 'triangle':
				return <div style={{width: 16, height: 16}}><TriangleShape /></div>
			case 'ellipse':
				return <div style={{width: 16, height: 16}}><EllipseShape /></div>
			default:
				return <></>
		}
	}

	return (
		<div style={{display: 'flex', gap: '10px', padding: '10px'}}>
			<button onClick={() => controller.addArtObject('rectangle')}
					style={buttonStyle}>{renderIcon('rectangle')}</button>
			<button onClick={() => controller.addArtObject('triangle')}
					style={buttonStyle}>{renderIcon('triangle')}</button>
			<button onClick={() => controller.addArtObject('ellipse')}
					style={buttonStyle}>{renderIcon('ellipse')}</button>
			<input
				id="inputImage"
				type="file"
				accept=".jpeg, .jpg, .png"
				onChange={handleImageUpload}
				style={{display: 'none'}}
			/>
			<button style={buttonStyle}>
				<label htmlFor="inputImage">{'Img'}</label>
			</button>
		</div>
	)
})

const HistoryBlock: React.FC<{
	controller: CanvasController,
	selectedShapeId?: string,
	handleDeleteShape: (shapeId: string) => void,
}> = ({controller, selectedShapeId, handleDeleteShape}) => {
	const buttonStyle: CSSProperties = {
		display: 'flex',
		justifyContent: 'center',
		alignItems: 'center',
		borderRadius: 5,
		border: 'solid 2px #413737'
	}

	return(
		<div style={{display: 'flex', gap: '10px', padding: '10px'}}>
			<button
				disabled={!controller.canUndo()}
				onClick={() => controller.undo()}
				style={buttonStyle}
			>
				{'Undo'}
			</button>
			<button
				disabled={!controller.canRedo()}
				onClick={() => controller.redo()}
				style={buttonStyle}
			>
				{'Redo'}
			</button>
			<button disabled={!selectedShapeId} onClick={() => handleDeleteShape(selectedShapeId!)} style={buttonStyle}>
				{'Delete shape'}
			</button>
		</div>
	)
}

export {
	Toolbar,
}
