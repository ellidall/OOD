// eslint-disable-next-line import/no-extraneous-dependencies
import '@testing-library/jest-dom'

class LocalStorageMock implements Storage {
	private store: Record<string, string> = {}

	get length(): number {
		return Object.keys(this.store).length
	}

	getItem(key: string): string | null {
		return this.store[key] || null
	}

	setItem(key: string, value: string): void {
		this.store[key] = value
	}

	removeItem(key: string): void {
		delete this.store[key]
	}

	clear(): void {
		this.store = {}
	}

	key(index: number): string | null {
		const keys = Object.keys(this.store)
		return keys[index] || null
	}
}

Object.defineProperty(global, 'localStorage', {
	value: new LocalStorageMock(),
	writable: true,
	configurable: true,
})
