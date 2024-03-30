#include "EmbedManager.h"


void EmbedManager::Generate(std::filesystem::path folderpath)
{
	m_fileManager.IterateFolder(folderpath, m_codeGenerator, FileHandle);
}

void EmbedManager::Export(std::filesystem::path outputpath)
{
	for (auto& file : m_codeGenerator.GetEmbededFiles())
	{
		// todo: export
	}
}

// static callback function used to iterate through each file
void EmbedManager::FileHandle(std::filesystem::path filepath, std::vector<uint8_t> content, CodeGenerator& codeGenerator)
{
	// MAGMA_TRACE("{0}", filepath.filename().string());

	if (content.empty()) return;

	codeGenerator.GenerateEmbed(filepath, content);
}