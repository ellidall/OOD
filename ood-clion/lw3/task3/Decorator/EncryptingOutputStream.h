#pragma once

#include <algorithm>
#include <memory>
#include "../OutputStream.h"

class EncryptingOutputStream : public IOutputDataStream
{
public:
    EncryptingOutputStream(std::unique_ptr<IOutputDataStream> s, uint32_t key) : m_stream(std::move(s))
    {
        std::vector<uint8_t> bytes(256);
        for (int i = 0; i < 256; i++)
        {
            bytes[i] = i;
        }
        std::mt19937 generator(key);
        std::shuffle(bytes.begin(), bytes.end(), generator);
        m_substitutionTable = bytes;
    }

    void WriteByte(uint8_t data) override
    {
        m_stream->WriteByte(m_substitutionTable[data]);
    }

    void WriteBlock(const void* srcData, std::streamsize size) override
    {
        const auto* data = static_cast<const uint8_t*>(srcData);
        std::vector<uint8_t> encrypted(size);
        for (std::streamsize i = 0; i < size; i++)
        {
            encrypted[i] = m_substitutionTable[data[i]];
        }
        m_stream->WriteBlock(encrypted.data(), size);
    }

    void Close() override
    {
        m_stream->Close();
    }

private:
    std::unique_ptr<IOutputDataStream> m_stream;
    std::vector<uint8_t> m_substitutionTable;
};