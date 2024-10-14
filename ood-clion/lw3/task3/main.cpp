#include <iostream>
#include <memory>
#include "InputStream.h"
#include "OutputStream.h"
#include "Decorator/DecryptingInputStream.h"
#include "Decorator/RLEInputStream.h"
#include "Decorator/EncryptingOutputStream.h"
#include "Decorator/RLEOutputStream.h"

int main(int argc, char** argv)
{
    if (argc < 4)
    {
        std::cout << "Error: Usage task3.exe [options] <input-file> <output-file>" << std::endl;
        return EXIT_FAILURE;
    }

    try
    {
        std::unique_ptr<IInputDataStream> inputPtr = std::make_unique<FileInputStream>(argv[argc - 2]);
        std::unique_ptr<IOutputDataStream> outputPtr = std::make_unique<FileOutputStream>(argv[argc - 1]);

        for (int i = 1; i <= argc - 3; i++)
        {
            if (std::strcmp(argv[i], "--encrypt") == 0 && i + 1 <= argc - 3)
            {
                uint32_t key = static_cast<uint32_t>(std::stoul(argv[++i]));
                outputPtr = std::make_unique<EncryptingOutputStream>(std::move(outputPtr), key);
            }
            else if (std::strcmp(argv[i], "--compress") == 0)
            {
                outputPtr = std::make_unique<RLEOutputStream>(std::move(outputPtr));
            }
            else if (std::strcmp(argv[i], "--decrypt") == 0 && i + 1 <= argc - 3)
            {
                uint32_t key = static_cast<uint32_t>(std::stoul(argv[++i]));
                inputPtr = std::make_unique<DecryptingInputStream>(std::move(inputPtr), key);
            }
            else if (std::strcmp(argv[i], "--decompress") == 0)
            {
                inputPtr = std::make_unique<RLEInputStream>(std::move(inputPtr));
            }
        }
        while (!inputPtr->IsEOF())
        {
            outputPtr->WriteByte(inputPtr->ReadByte());
        }
        outputPtr->Close();
    }
    catch (const std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}