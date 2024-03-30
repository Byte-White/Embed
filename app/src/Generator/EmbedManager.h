#ifndef EMBED_EMBED_MANAGER_H
#define EMBED_EMBED_MANAGER_H
#include "FileManager.h"
#include "CodeGenerator.h"

class EmbedManager
{
public:
	void Generate(std::filesystem::path folderpath);
	void Export(std::filesystem::path outputpath);
private:
	static void FileHandle(std::filesystem::path filepath, std::vector<uint8_t> content,CodeGenerator& codeGenerator);
private:
	FileManager m_fileManager;
	CodeGenerator m_codeGenerator;
};

#endif //EMBED_EMBED_MANAGER_H