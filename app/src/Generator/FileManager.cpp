#include "FileManager.h"

void FileManager::IterateFolder(std::filesystem::path path, CodeGenerator& codeGenerator,
	void (*func)(std::filesystem::path filepath, std::vector<uint8_t> content, CodeGenerator& codeGenerator)
)
{
    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
        if (std::filesystem::is_regular_file(entry))
        {
			std::vector<uint8_t> content = LoadFileContent(entry.path().string());
            func(entry.path(), content, codeGenerator);
        }
        else if (std::filesystem::is_directory(entry))
        {
            IterateFolder(entry.path(),codeGenerator ,func);
        }
    }
}

std::vector<uint8_t> FileManager::LoadFileContent(std::string filepath)
{
	std::ifstream file(filepath);
	if (!file.good())
	{
		MAGMA_ERROR("Could not open file '{0}'", filepath);
		return {};
	}
	file.seekg(0, std::ios::end);
	std::streampos fileSize = file.tellg();
	file.seekg(0, std::ios::beg);
	std::vector<uint8_t> result(fileSize);

	file.read(reinterpret_cast<char*>(result.data()), fileSize);
	if (!file)
	{
		MAGMA_ERROR("Error reading file '{0}'", filepath);
		return {};
	}
	return result;
}