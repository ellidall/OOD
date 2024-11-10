#pragma once

#include "../Path.h"

class IImage
{
public:
	[[nodiscard]] virtual Path GetPath() const = 0;
	[[nodiscard]] virtual unsigned GetWidth() const = 0;
	[[nodiscard]] virtual unsigned GetHeight() const = 0;
	virtual void Resize(unsigned width, unsigned height) = 0;
	virtual ~IImage() = default;
};