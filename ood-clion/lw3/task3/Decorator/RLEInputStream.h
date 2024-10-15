#pragma once

#include <random>
#include <memory>
#include "../InputStream.h"

class RLEInputStream : public IInputDataStream
{
public:
    explicit RLEInputStream(std::unique_ptr<IInputDataStream> s) : m_stream(std::move(s)), m_count(0), m_currentByte(0)
    {}

    [[nodiscard]] bool IsEOF() override
    {
        return m_stream->IsEOF() && m_count == 0;
    }

    uint8_t ReadByte() override
    {
        if (m_count == 0)
        {
            if (IsEOF())
            {
                return 0;
            }
            m_count = m_stream->ReadByte();
            m_currentByte = m_stream->ReadByte();
        }

        m_count--;
        return m_currentByte;
    }

    std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
    {
        auto* buffer = static_cast<uint8_t*>(dstBuffer);
        std::streamsize bytesRead = 0;

        while (bytesRead < size && !IsEOF())
        {
            buffer[bytesRead++] = ReadByte();
        }

        return bytesRead;
    }

private:
    std::unique_ptr<IInputDataStream> m_stream;
    uint8_t m_currentByte;
    uint8_t m_count;
};