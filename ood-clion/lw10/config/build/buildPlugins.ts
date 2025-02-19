import react from '@vitejs/plugin-react'
import {PluginOption} from 'vite'

const buildPlugins = (): PluginOption[] => ([
	react(),
])

export {
	buildPlugins,
}