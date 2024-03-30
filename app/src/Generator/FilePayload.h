#ifndef EMBED_FILEPAYLOAD_H
#define EMBED_FILEPAYLOAD_H

#include <filesystem>
#include <string>
#include <vector>

struct FilePayload
{
	std::filesystem::path filepath;
	std::string variableName;
	std::string embedcontent;
};
#endif //EMBED_FILEPAYLOAD_H