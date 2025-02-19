import {ResolveOptions as ViteResolveOptions, AliasOptions} from 'vite'
import {BuildOptions} from './types/config'

type ResolveOptions = ViteResolveOptions & {
	alias?: AliasOptions,
}

const buildResolve = (args: BuildOptions): ResolveOptions => ({
	alias: args.aliases,
})

export {
	buildResolve,
}