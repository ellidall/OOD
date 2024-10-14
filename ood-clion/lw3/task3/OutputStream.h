#pragma once

#include <iostream>
#include <fstream>
#include <random>

class IOutputDataStream
{
public:
    virtual void WriteByte(uint8_t data) = 0;
    virtual void WriteBlock(const void* srcData, std::streamsize size) = 0;
    virtual void Close() = 0;
    virtual ~IOutputDataStream() = default;
};

class FileOutputStream : public IOutputDataStream
{
public:
    explicit FileOutputStream(const std::string& filename)
    {
        m_file.open(filename, std::ios::binary);
        if (!m_file.is_open()) throw std::ios_base::failure("Failed to open the file for writing");
    }

    void WriteByte(uint8_t data) override
    {
        m_file.write(reinterpret_cast<const char*>(&data), sizeof(data));
        if (m_file.fail()) throw std::ios_base::failure("Byte write error");
    }

    void WriteBlock(const void* srcData, std::streamsize size) override
    {
        m_file.write(static_cast<const char*>(srcData), size);
        if (m_file.fail()) throw std::ios_base::failure("Block write error");
    }

    void Close() override
    {
        m_file.close();
    }

private:
    std::ofstream m_file;
};

class MemoryOutputStream : public IOutputDataStream
{
public:
    void WriteByte(uint8_t data) override
    {
        m_buffer.push_back(data);
    }

    void WriteBlock(const void* srcData, std::streamsize size) override
    {
        const auto* data = static_cast<const uint8_t*>(srcData);
        m_buffer.insert(m_buffer.end(), data, data + size);
    }

    void Close() override
    {}

    [[nodiscard]] const std::vector<uint8_t>& GetBuffer() const
    {
        return m_buffer;
    }

private:
    std::vector<uint8_t> m_buffer;
};
