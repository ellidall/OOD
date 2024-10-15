#pragma once

#include <random>
#include <memory>
#include "../OutputStream.h"

class RLEOutputStream : public IOutputDataStream
{
public:
    explicit RLEOutputStream(std::unique_ptr<IOutputDataStream> s) : m_stream(std::move(s)), m_count(0), m_currentByte(0)
    {}

    void WriteByte(uint8_t data) override
    {
        if (m_count == 0)
        {
            m_currentByte = data;
            m_count = 1;
        }
        else if (data == m_currentByte && m_count < 255)
        {
            m_count++;
        }
        else
        {
            Flush();
            m_currentByte = data;
            m_count = 1;
        }
    }

    void WriteBlock(const void* srcData, std::streamsize size) override
    {
        const auto* data = static_cast<const uint8_t*>(srcData);
        for (std::streamsize i = 0; i < size; ++i)
        {
            WriteByte(data[i]);
        }
    }

    void Close() override
    {
        Flush();
        m_stream->Close();
    }

private:
    std::unique_ptr<IOutputDataStream> m_stream;
    uint8_t m_currentByte;
    uint8_t m_count;

    void Flush()
    {
        if (m_count > 0)
        {
            m_stream->WriteByte(m_count);
            m_stream->WriteByte(m_currentByte);
            m_count = 0;
        }
    }
};