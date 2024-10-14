#pragma once

#include <iostream>
#include <fstream>
#include <random>
#include <cstring>

class IInputDataStream
{
public:
    [[nodiscard]] virtual bool IsEOF() = 0;
    virtual uint8_t ReadByte() = 0;
    virtual std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) = 0;
    virtual ~IInputDataStream() = default;
};

class FileInputStream : public IInputDataStream
{
public:
    explicit FileInputStream(const std::string& filename)
    {
        m_file.open(filename, std::ios::binary);
        if (!m_file.is_open()) throw std::ios_base::failure("Failed to open the file for reading");
    }

    bool IsEOF() override
    {
        return m_file.peek() == std::ifstream::traits_type::eof();
    }

    uint8_t ReadByte() override
    {

        uint8_t data;
        if (!IsEOF()) m_file.read(reinterpret_cast<char*>(&data), sizeof(data));
        if (m_file.fail()) throw std::ios_base::failure("Byte read error");
        return data;
    }

    std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
    {
        if (!IsEOF()) m_file.read(static_cast<char*>(dstBuffer), size);
        if (m_file.fail()) throw std::ios_base::failure("Block read error");
        return m_file.gcount();
    }

private:
    std::ifstream m_file;
};

class MemoryInputStream : public IInputDataStream
{
public:
    explicit MemoryInputStream(const std::vector<uint8_t>& data)
            : m_buffer(data), m_position(0)
    {}

    bool IsEOF() override
    {
        return m_position >= m_buffer.size();
    }

    uint8_t ReadByte() override
    {
        if (IsEOF())
        {
            throw std::ios_base::failure("End of stream reached");
        }
        return m_buffer[m_position++];
    }

    std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
    {
        if (IsEOF())
        {
            return 0;
        }

        std::streamsize bytesToRead = std::min(size, static_cast<std::streamsize>(m_buffer.size() - m_position));

        std::memcpy(dstBuffer, m_buffer.data() + m_position, bytesToRead);
        m_position += bytesToRead;

        return bytesToRead;
    }

private:
    const std::vector<uint8_t>& m_buffer;
    size_t m_position;
};
