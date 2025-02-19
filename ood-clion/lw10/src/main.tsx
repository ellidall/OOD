import {createRoot} from 'react-dom/client'
import {App} from './components/App'
import {CanvasController} from './controllers/CanvasController'
import {ShapeController} from './controllers/ShapeController'
import {CanvasModel} from './models/CanvasModel'

const root = document.getElementById('root')

const model = new CanvasModel()
if (root) {
	createRoot(root).render(
		<div>
			<div style={{display: 'flex', flexDirection: 'column', overflowX: 'hidden'}}>
				<App model={model} canvasController={new CanvasController(model)} shapeController={new ShapeController(model)}/>
				<App model={model} canvasController={new CanvasController(model)} shapeController={new ShapeController(model)}/>
			</div>
		</div>,
	)
}