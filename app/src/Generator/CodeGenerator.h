#ifndef EMBED_CODE_GENERATOR_H
#define EMBED_CODE_GENERATOR_H

#include <filesystem>
#include <string>
#include <vector>

#include "FilePayload.h"


class HeaderGenerator
{
	using FilePayloadsVec = std::vector<FilePayload>;
public:
	static void AddClassBeginning(std::stringstream& headerStream, const FilePayloadsVec& embeddedFiles);
	static void AddClassEnding(std::stringstream& headerStream, const FilePayloadsVec& embeddedFiles);
	static void AddHandleFunctionsDeclarations(std::stringstream& headerStream, const FilePayloadsVec& embeddedFiles);
};

class SourceGenerator
{
	using FilePayloadsVec = std::vector<FilePayload>;
public:
	static void AddIncludes(std::stringstream& sourceStream, const FilePayloadsVec& embeddedFiles);
	static void AddBeginServerFunction(std::stringstream& sourceStream, const FilePayloadsVec& embeddedFiles);
	static void AddHandleClientFunction(std::stringstream& sourceStream, const FilePayloadsVec& embeddedFiles);
	static void AddHandleFunctionsImplementations(std::stringstream& sourceStream, const FilePayloadsVec& embeddedFiles);
};

class CodeGenerator
{
public:
	void GenerateEmbed(std::filesystem::path filepath, std::vector<uint8_t> content, std::filesystem::path basepath);
	ServerClassPayload GenerateServerClass();

	inline std::vector<FilePayload>& GetEmbededFiles() { return m_embeddedFiles; }
private:
	std::string GenerateHeaderFileContent();
	std::string GenerateSourceFileContent();
private:
	std::vector<FilePayload> m_embeddedFiles;
};

#endif //EMBED_CODE_GENERATOR_H