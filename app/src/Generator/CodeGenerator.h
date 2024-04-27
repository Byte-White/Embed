#ifndef EMBED_CODE_GENERATOR_H
#define EMBED_CODE_GENERATOR_H

#include <filesystem>
#include <string>
#include <vector>

#include "FilePayload.h"

class CodeGenerator
{
public:
	void GenerateEmbed(std::filesystem::path filepath, std::vector<uint8_t> content, std::filesystem::path basepath);
	ServerClassPayload GenerateServerClass();

	inline std::vector<FilePayload>& GetEmbededFiles() { return m_embededFiles; }
private:
	std::string GenerateHeaderFileContent();
	std::string GenerateSourceFileContent();
private:
	std::vector<FilePayload> m_embededFiles;
};

#endif //EMBED_CODE_GENERATOR_H