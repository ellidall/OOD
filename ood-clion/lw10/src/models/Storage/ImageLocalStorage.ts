type ImageData = {
	imageId: string,
	data: string,
}

type ImageStorage = {
	images: ImageData[],
}

class ImageLocalStorage {
	private static readonly STORAGE_KEY = 'images_storage'

	static getImageData(imageId: string): string | undefined {
		const storage = this.getStorage()
		const image = storage.images.find(img => img.imageId === imageId)
		return image ? image.data : undefined
	}

	static removeImage(imageId: string): void {
		const storage = this.getStorage()
		storage.images = storage.images.filter(img => img.imageId !== imageId)
		this.saveStorage(storage)
	}

	static addImage(imageId: string, data: string): void {
		const storage = this.getStorage()

		const existingImageIndex = storage.images.findIndex(img => img.imageId === imageId)

		if (existingImageIndex === -1) {
			storage.images.push({imageId, data})
		}
		else {
			storage.images[existingImageIndex]!.data = data
		}

		this.saveStorage(storage)
	}

	static clearStorage(): void {
		localStorage.clear()
	}

	private static getStorage(): ImageStorage {
		const storedData = localStorage.getItem(ImageLocalStorage.STORAGE_KEY)
		return storedData ? JSON.parse(storedData) : {images: []}
	}

	private static saveStorage(storage: ImageStorage): void {
		localStorage.setItem(ImageLocalStorage.STORAGE_KEY, JSON.stringify(storage))
	}
}

export {
	ImageLocalStorage,
}