#ifndef EMBED_FILE_MANAGER_H
#define EMBED_FILE_MANAGER_H

#include <filesystem>
#include <string>
#include <fstream>
#include <vector>

#include "Magma/Core/Logging.h"

class FileManager
{
public:
	void IterateFolder(std::filesystem::path path, void (*func)(std::string filename, std::vector<uint8_t> content));

	std::vector<uint8_t> LoadFileContent(std::string filepath);
};
#endif //EMBED_FILE_MANAGER_H