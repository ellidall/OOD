import {UserConfig} from 'vite'
import {buildPlugins} from './buildPlugins'
import {buildResolve} from './buildResolve'
import {buildServer} from './buildServer'
import {BuildOptions} from './types/config'

const buildViteConfig = (args: BuildOptions): UserConfig => ({
	mode: args.mode,
	plugins: buildPlugins(),
	server: buildServer(args),
	resolve: buildResolve(args),
})

export {
	buildViteConfig,
}