#pragma once

#include <utility>

#include "IParagraph.h"

class CParagraph : public IParagraph
{
public:
    explicit CParagraph(std::string text) : m_text(std::move(text))
    {
    }

    [[nodiscard]] std::string GetText() const override
    {
        return m_text;
    }

    void SetText(const std::string& text) override
    {
        m_text = text;
    }

private:
    std::string m_text;
};