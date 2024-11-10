#pragma once

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <filesystem>

class FileUtils
{
public:
	static std::string GetFileName(const Path &path)
	{
		std::cout << path << std::endl;
		size_t slashPosition = path.find_last_of('/');
		std::cout << slashPosition << std::endl;

		if (slashPosition != std::string::npos && slashPosition != 0)
		{
			return path.substr(slashPosition + 1);
		}

		return "";
	}

	static std::string GetFileExtension(const Path &path)
	{
		size_t dotPosition = path.find_last_of('.');

		if (dotPosition != std::string::npos && dotPosition != 0)
		{
			return path.substr(dotPosition + 1);
		}

		return "";
	}

	static std::string GenerateRandomFileName(const std::string &extension)
	{
		const auto now = std::chrono::system_clock::now();
		const auto nowMs = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

		return std::format("file_{}.{}", nowMs, extension);
	}

	static void CopyFile(const std::string &inputFilePath, const std::string &outputFilePath)
	{
		std::ifstream inputFile(inputFilePath);
		if (!inputFile.is_open()) throw std::runtime_error("Failed to open " + inputFilePath + " for reading.");

		const std::filesystem::path outputDir = std::filesystem::path(outputFilePath).parent_path();
		if (!outputDir.empty() && !exists(outputDir)) create_directories(outputDir);

		std::ofstream outputFile(outputFilePath);
		if (!outputFile.is_open())throw std::runtime_error("Failed to open " + outputFilePath + " for writing.");

		CopyStreams(inputFile, outputFile);
		if (!inputFile.eof()) throw std::runtime_error("Error reading input file.");
	}

	static void DeleteFileIfExists(const std::string &filePath)
	{
		if (std::filesystem::exists(filePath)) std::filesystem::remove(filePath);
	}

private:
	static void CopyStreams(std::istream &inputFile, std::ostream &outputFile)
	{
		char buffer[4096];
		while (inputFile)
		{
			inputFile.read(buffer, sizeof(buffer));
			outputFile.write(buffer, inputFile.gcount());

			if (!outputFile)
			{
				throw std::runtime_error("Failed to save data on disk.");
			}
		}
	}
};