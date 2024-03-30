#ifndef EMBED_FILE_MANAGER_H
#define EMBED_FILE_MANAGER_H

#include <filesystem>
#include <string>
#include <fstream>
#include <vector>

#include "Magma/Core/Logging.h"
#include "CodeGenerator.h"

class FileManager
{
public:
	void IterateFolder(std::filesystem::path path, CodeGenerator& codeGenerator,
		void (*func)(std::filesystem::path filepath,
			std::vector<uint8_t> content,
			CodeGenerator& codeGenerator));

	std::vector<uint8_t> LoadFileContent(std::string filepath);
};
#endif //EMBED_FILE_MANAGER_H