import {ServerOptions} from 'vite'
import {BuildOptions} from './types/config'

const buildServer = (args: BuildOptions): ServerOptions => ({
	port: args.port,
	open: args.paths.html,
})

export {
	buildServer,
}