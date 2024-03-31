#ifndef EMBED_FILEPAYLOAD_H
#define EMBED_FILEPAYLOAD_H

#include <filesystem>
#include <string>
#include <vector>

struct FilePayload
{
	std::filesystem::path filepath;
	std::filesystem::path relativepath;
	std::string variableName;
	std::string embedcontent;
	uint32_t filesize;
};


struct ServerClassPayload
{
	std::string headercontent;
	std::string cppcontent;
};
#endif //EMBED_FILEPAYLOAD_H