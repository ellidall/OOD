#include <gtest/gtest.h>
#include "../task3/InputStream.h"
#include "../task3/OutputStream.h"
#include "../task3/Decorator/EncryptingOutputStream.h"
#include "../task3/Decorator/DecryptingInputStream.h"
#include "../task3/Decorator/RLEInputStream.h"
#include "../task3/Decorator/RLEOutputStream.h"
#include <fstream>
#include <vector>

TEST(MemoryOutputStreamTest, WriteAndRead) {

    MemoryOutputStream memoryStream;
    uint8_t data[] = { 0x01, 0x02, 0x03 };
    memoryStream.WriteBlock(data, sizeof(data));

    const auto& buffer = memoryStream.GetBuffer();
    ASSERT_EQ(buffer.size(), 3);
    EXPECT_EQ(buffer[0], 0x01);
    EXPECT_EQ(buffer[1], 0x02);
    EXPECT_EQ(buffer[2], 0x03);
}

TEST(MemoryInputStreamTest, ReadByte) {
    std::vector<uint8_t> data = { 0x01, 0x02, 0x03 };
    MemoryInputStream memoryInputStream(data);

    EXPECT_EQ(memoryInputStream.ReadByte(), 0x01);
    EXPECT_EQ(memoryInputStream.ReadByte(), 0x02);
    EXPECT_EQ(memoryInputStream.ReadByte(), 0x03);
    EXPECT_THROW(memoryInputStream.ReadByte(), std::ios_base::failure);
}

class MockMemoryOutputStream : public IOutputDataStream
{
public:
    explicit MockMemoryOutputStream(std::vector<uint8_t>& data) : m_buffer(data)
    {}

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

private:
    std::vector<uint8_t>& m_buffer;
};

TEST(EncryptionTest, EncryptDecrypt) {
    const uint32_t key = 12345;
    std::vector<uint8_t> data;
    EncryptingOutputStream encryptingStream(std::make_unique<MockMemoryOutputStream>(data), key);
    std::vector<uint8_t> buffer = { 0, 1, 2 };

    encryptingStream.WriteBlock(buffer.data(), static_cast<std::streamsize>(buffer.size()));

    DecryptingInputStream decryptingStream(std::make_unique<MemoryInputStream>(data), key);
    uint8_t decryptedData[3];
    decryptingStream.ReadBlock(decryptedData, sizeof(decryptedData));

    EXPECT_EQ(decryptedData[0], buffer[0]);
    EXPECT_EQ(decryptedData[1], buffer[1]);
    EXPECT_EQ(decryptedData[2], buffer[2]);
}

TEST(MultyEncryptionTest, MyltyEncryptDecrypt) {
    const uint32_t key1 = 12345;
    const uint32_t key2 = 23;
    std::vector<uint8_t> data;
    std::unique_ptr<IOutputDataStream> outputPtr = std::make_unique<MockMemoryOutputStream>(data);
    outputPtr = std::make_unique<EncryptingOutputStream>(std::move(outputPtr), key1);
    outputPtr = std::make_unique<EncryptingOutputStream>(std::move(outputPtr), key2);
    std::vector<uint8_t> buffer = { 3, 4, 5 };

    outputPtr->WriteBlock(buffer.data(), static_cast<std::streamsize>(buffer.size()));

    std::unique_ptr<IInputDataStream> inputPtr = std::make_unique<MemoryInputStream>(data);
    inputPtr = std::make_unique<DecryptingInputStream>(std::move(inputPtr), key1);
    inputPtr = std::make_unique<DecryptingInputStream>(std::move(inputPtr), key2);
    uint8_t decryptedData[3];
    inputPtr->ReadBlock(decryptedData, sizeof(decryptedData));

    EXPECT_EQ(decryptedData[0], buffer[0]);
    EXPECT_EQ(decryptedData[1], buffer[1]);
    EXPECT_EQ(decryptedData[2], buffer[2]);
}

TEST(RLETest, RLECompression) {
    std::vector<uint8_t> data;
    RLEOutputStream rleOutputStream(std::make_unique<MockMemoryOutputStream>(data));
    std::vector<uint8_t> buffer = { 0, 1, 2, 3, 4, 5 };

    rleOutputStream.WriteBlock(buffer.data(), static_cast<std::streamsize>(buffer.size()));

    RLEInputStream rleInputStream(std::make_unique<MemoryInputStream>(data));
    uint8_t decompressedData[6];
    rleInputStream.ReadBlock(decompressedData, sizeof(decompressedData));

    EXPECT_EQ(decompressedData[0], buffer[0]);
    EXPECT_EQ(decompressedData[1], buffer[1]);
    EXPECT_EQ(decompressedData[2], buffer[2]);
    EXPECT_EQ(decompressedData[3], buffer[3]);
    EXPECT_EQ(decompressedData[4], buffer[4]);
}