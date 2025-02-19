import {Component} from 'react'
import {CanvasController} from '../controllers/CanvasController'
import {ShapeController} from '../controllers/ShapeController'
import {ICanvasReadModel} from '../models/CanvasModel'
import {Canvas} from './Canvas/Canvas'
import {Toolbar} from './Toolbar/Toolbar'

type AppProps = {
	model: ICanvasReadModel,
	canvasController: CanvasController,
	shapeController: ShapeController,
}

type AppState = {
	model: ICanvasReadModel,
	canvasController: CanvasController,
	shapeController: ShapeController,
	selectedShapeId?: string,
}

class App extends Component<AppProps, AppState> {
	constructor(props: AppProps) {
		super(props)
		this.state = {
			model: this.props.model,
			canvasController: this.props.canvasController,
			shapeController: this.props.shapeController,
		}
	}

	handleSelectShape = (shapeId?: string) => {
		this.setState({selectedShapeId: shapeId})
	}

	handleDeleteShape = (shapeId: string) => {
		this.state.canvasController.removeShape(shapeId)
	}

	override render() {
		return (
			<div style={{display: 'flex'}}>
				<div style={{margin: '0 auto'}}>
					<Toolbar
						canvasModel={this.state.model}
						controller={this.state.canvasController}
						selectedShapeId={this.state.selectedShapeId}
						setSelectedShapeId={this.handleSelectShape}
						handleDeleteShape={this.handleDeleteShape}
					/>
					<Canvas
						model={this.state.model}
						canvasController={this.state.canvasController}
						shapeController={this.state.shapeController}
						handleSelectShape={this.handleSelectShape}
						selectedShapeId={this.state.selectedShapeId}
						handleDeleteShape={this.handleDeleteShape}
					/>
				</div>
			</div>
		)
	}
}

export {
	App,
}