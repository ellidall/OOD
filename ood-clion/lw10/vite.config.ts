import * as path from 'path'
import url from 'url'
import {ConfigEnv} from 'vite'
import {buildViteConfig} from './config/build/buildViteConfig'
import {BuildAliases, BuildMode, BuildPaths} from './config/build/types/config'

const __filename = url.fileURLToPath(import.meta.url)
const __dirname = path.dirname(__filename)

export default (configEnv: ConfigEnv) => {
	const mode = (configEnv.mode ?? 'development') as BuildMode
	const isDev = mode === 'development'
	const paths: BuildPaths = {
		html: '',
		entry: path.resolve(__dirname, 'src', 'main.tsx'),
	}

	const aliases: BuildAliases = {
		components: path.resolve(__dirname, 'src', 'components'),
		controllers: path.resolve(__dirname, 'src', 'controllers'),
		models: path.resolve(__dirname, 'src', 'models'),
		services: path.resolve(__dirname, 'src', 'services'),
		types: path.resolve(__dirname, 'src', 'types'),
		utils: path.resolve(__dirname, 'src', 'utils'),
		svg: path.resolve(__dirname, 'src', 'svg'),
	}

	return buildViteConfig({
		isDev,
		mode,
		paths,
		aliases,
		port: 3000,
	})
}
