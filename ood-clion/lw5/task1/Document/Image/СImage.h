#pragma once

#include <utility>

#include "IImage.h"

class CImage : public IImage
{
public:
	CImage(
		Path path,
		const unsigned width,
		const unsigned height
	): m_path(std::move(path)),
	   m_width(width),
	   m_height(height)
	{
	}

	[[nodiscard]] Path GetPath() const override
	{
		return m_path;
	}

	[[nodiscard]] unsigned GetWidth() const override
	{
		return m_width;
	}

	[[nodiscard]] unsigned GetHeight() const override
	{
		return m_height;
	}

	void Resize(const unsigned width, const unsigned height) override
	{
		m_width = width;
		m_height = height;
	}

private:
	Path m_path;
	unsigned m_width;
	unsigned m_height;
};