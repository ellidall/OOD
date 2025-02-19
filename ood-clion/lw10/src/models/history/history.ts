import {ICommand} from 'models/Command/commands'

class History {
	private static readonly MAX_COMMANDS_COUNT = 10
	private commands: ICommand[] = []
	private currentActionIndex = 0

	canUndo(): boolean {
		return this.currentActionIndex > 0
	}

	canRedo(): boolean {
		return this.currentActionIndex < this.commands.length
	}

	undo(): void {
		if (this.canUndo()) {
			this.commands[--this.currentActionIndex]?.unexecute()
		}
	}

	redo(): void {
		if (this.canRedo()) {
			this.commands[this.currentActionIndex++]?.execute()
		}
	}

	clear(): void {
		for (const command of this.commands) {
			command.destroy()
		}
		this.currentActionIndex = 0
		this.commands = []
	}

	addAndExecuteCommand(command: ICommand): void {
		command.execute()
		if (this.currentActionIndex < this.commands.length) {
			for (let i = this.currentActionIndex; i < this.commands.length; i++) {
				this.commands[i]?.destroy()
			}
			this.commands.splice(this.currentActionIndex, this.commands.length - this.currentActionIndex)
		}

		const lastCommand = this.commands[this.currentActionIndex - 1]

		if (lastCommand?.canMergeWith(command)) {
			lastCommand.mergeWith(command)
		}
		else {
			this.commands.push(command)
			this.currentActionIndex++
		}

		if (this.commands.length > History.MAX_COMMANDS_COUNT) {
			this.commands.shift()
			this.currentActionIndex--
		}
	}
}

export {
	History,
}