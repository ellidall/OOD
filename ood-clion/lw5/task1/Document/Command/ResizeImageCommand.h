#pragma once

#include <vector>
#include "../CDocumentItem.h"
#include "AbstractCommand.h"

class ResizeImageCommand : public AbstractCommand
{
public:
	ResizeImageCommand(
		const size_t position,
		const unsigned width,
		const unsigned height,
		std::vector<CDocumentItem> &items
	): m_newWidth(width),
	   m_newHeight(height),
	   m_position(position),
	   m_items(items)
	{
	}

	void DoExecute() override
	{
		if (m_position >= m_items.size()) throw std::invalid_argument("Position out of range");

		auto item = m_items.at(m_position);
		const auto image = item.GetImage();

		if (image == nullptr) throw std::invalid_argument("This item is not a image");

		m_previousWidth = image->GetWidth();
		m_previousHeight = image->GetHeight();

		image->Resize(m_newWidth, m_newHeight);
	}

	void DoUnexecute() override
	{
		if (m_position >= m_items.size()) throw std::invalid_argument("Position out of range");

		auto item = m_items.at(m_position);
		const auto image = item.GetImage();

		if (image == nullptr) throw std::invalid_argument("This item is not a image");

		m_newWidth = image->GetWidth();
		m_newHeight = image->GetHeight();

		image->Resize(m_previousWidth, m_previousHeight);
	}

	void Destroy() override
	{
	}

private:
	unsigned m_previousWidth{};
	unsigned m_newWidth;
	unsigned m_previousHeight{};
	unsigned m_newHeight;
	size_t m_position;
	std::vector<CDocumentItem> &m_items;
};