import React, {ChangeEvent, Component} from 'react'
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
			<div style={{display: 'flex', gap: '10px'}}>
				<CreateArtObjectBlock controller={this.controller} />
				<ImageImportBlock controller={this.controller} />
				<JsonBlock controller={this.controller} model={this.canvasModel} onLoad={() => this.props.setSelectedShapeId(undefined)}/>
				<HistoryBlock controller={this.controller}/>
				<ShapeControlBlock
					selectedShapeId={this.props.selectedShapeId}
					handleDeleteShape={this.props.handleDeleteShape}
				/>
			</div>
		)
	}
}

const CreateArtObjectBlock = React.memo(({controller}: {controller: CanvasController}) => {
	const onCreateArt = (type: ArtObjectType) => {
		controller.addArtObject(type)
	}

	return (
		<div style={{display: 'flex', gap: '10px', padding: '10px', background: '#e0e0e0', borderRadius: '5px'}}>
			<button onClick={() => onCreateArt('rectangle')}>{renderIcon('rectangle')}{' Rectangle'}</button>
			<button onClick={() => onCreateArt('triangle')}>{renderIcon('triangle')}{' Triangle'}</button>
			<button onClick={() => onCreateArt('ellipse')}>{renderIcon('ellipse')}{' Ellipse'}</button>
		</div>
	)
})

const renderIcon = (type: ArtObjectType): JSX.Element => {
	switch (type) {
		case 'rectangle':
			return <div style={{width: 16, height: 16}}><RectangleShape /></div>
		case 'triangle':
			return <div style={{width: 16, height: 16}}><TriangleShape /></div>
		case 'ellipse':
			return <div style={{width: 16, height: 16}}><EllipseShape /></div>
		default:
			return <></>
	}
}

const ImageImportBlock = React.memo(({controller}: {controller: CanvasController}) => {
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

	return (
		<div style={{display: 'flex', padding: '10px', background: '#e0e0e0', borderRadius: '5px'}}>
			<input
				id="input-image-from-pc"
				type="file"
				accept=".jpeg, .jpg, .png"
				onChange={handleImageUpload}
				style={{display: 'none'}}
			/>
			<button>
				<label htmlFor="input-image-from-pc">
					{'Upload an image'}
				</label>
			</button>
		</div>
	)
})

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
}

const handleSaveJson = (jsonData: string) => {
	const blob = new Blob([jsonData], {type: 'application/json'})
	const url = URL.createObjectURL(blob)
	const a = document.createElement('a')
	a.href = url
	a.download = 'CanvasData.json'
	a.click()
	URL.revokeObjectURL(url)
	alert('Canvas data saved successfully.')
}

const JsonBlock = React.memo(({controller, model, onLoad}: {controller: CanvasController, model: ICanvasReadModel, onLoad: () => void}) => (
	<div style={{display: 'flex', gap: '10px', padding: '10px', background: '#e0e0e0', borderRadius: '5px'}}>
		<button onClick={() => {
			handleSaveJson(model.serializeCanvasToJson())
		}}>
			{'Save JSON'}
		</button>
		<input
			id="input-json-from-pc"
			type="file"
			accept=".json"
			onChange={e => {
				handleLoadJson(e, controller)
				onLoad()
			}}
			style={{display: 'none'}}
		/>
		<button>
			<label htmlFor="input-json-from-pc">
				{'Load JSON'}
			</label>
		</button>
	</div>
))

const ShapeControlBlock = React.memo(({selectedShapeId, handleDeleteShape}: {
	selectedShapeId?: string,
	handleDeleteShape: (shapeId: string) => void,
}) => {
	if (!selectedShapeId) {
		return null
	}

	return (
		<div style={{display: 'flex', gap: '10px', padding: '10px', background: '#e0e0e0', borderRadius: '5px'}}>
			<button onClick={() => handleDeleteShape(selectedShapeId)}>
				{'Delete shape'}
			</button>
		</div>
	)
})

const HistoryBlock = ({controller}: {controller: CanvasController}) => (
	<div style={{display: 'flex', gap: '10px', padding: '10px', background: '#e0e0e0', borderRadius: '5px'}}>
		<button
			disabled={!controller.canUndo()}
			onClick={() => controller.undo()}
		>
			{'Undo'}
		</button>
		<button
			disabled={!controller.canRedo()}
			onClick={() => controller.redo()}
		>
			{'Redo'}
		</button>
	</div>
)

const MemoizedToolbar = React.memo(Toolbar)

export {
	MemoizedToolbar as Toolbar,
}
