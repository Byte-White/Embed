#ifndef EMBED_EMBED_MANAGER_H
#define EMBED_EMBED_MANAGER_H
#include "FileManager.h"
#include "CodeGenerator.h"

class EmbedManager
{
public:
	void Generate(std::filesystem::path folderpath);
	void Export(std::filesystem::path outputpath);

	inline std::vector<FilePayload>& GetEmbededFiles() { return m_codeGenerator.GetEmbededFiles(); }

	inline std::filesystem::path& GetBasePath() { return s_basepath; }

private:
	static void FileHandle(std::filesystem::path filepath, std::vector<uint8_t> content,CodeGenerator& codeGenerator);
private:
	FileManager m_fileManager;
	CodeGenerator m_codeGenerator;
	static std::filesystem::path s_basepath;
};

#endif //EMBED_EMBED_MANAGER_H