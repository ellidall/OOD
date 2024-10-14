#pragma once

#include <algorithm>
#include <memory>
#include "../InputStream.h"

class DecryptingInputStream : public IInputDataStream
{
public:
    DecryptingInputStream(std::unique_ptr<IInputDataStream> s, uint32_t key) : m_stream(std::move(s))
    {
        std::vector<uint8_t> bytes(256);
        for (int i = 0; i < 256; i++)
        {
            bytes[i] = i;
        }
        std::mt19937 generator(key);
        std::shuffle(bytes.begin(), bytes.end(), generator);

        m_substitutionTable.resize(256);
        for (int i = 0; i < 256; ++i)
        {
            m_substitutionTable[bytes[i]] = i;
        }
    }

    uint8_t ReadByte() override
    {
        uint8_t encryptedByte = m_stream->ReadByte();
        return m_substitutionTable[encryptedByte];
    }

    std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
    {
        auto* buffer = static_cast<uint8_t*>(dstBuffer);
        std::vector<uint8_t> encrypted(size);
        std::streamsize bytesRead = m_stream->ReadBlock(encrypted.data(), size);

        for (std::streamsize i = 0; i < bytesRead; i++)
        {
            buffer[i] = m_substitutionTable[encrypted[i]];
        }
        return bytesRead;
    }

    [[nodiscard]] bool IsEOF() override
    {
        return m_stream->IsEOF();
    }

private:
    std::unique_ptr<IInputDataStream> m_stream;
    std::vector<uint8_t> m_substitutionTable;
};