type ArtObjectType = 'rectangle' | 'triangle' | 'ellipse'
type ShapeType = ArtObjectType | 'image'
type ShapeSize = {
	width: number,
	height: number,
}
type ShapePosition = {
	x: number,
	y: number,
}

export type {
	ArtObjectType,
	ShapeType,
	ShapeSize,
	ShapePosition,
}