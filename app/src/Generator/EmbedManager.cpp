#include "EmbedManager.h"
#include "HttpRequestHeaderEmbed.h"
#include "HttpRequestSourceEmbed.h"

std::filesystem::path EmbedManager::s_basepath = "";

void EmbedManager::Generate(std::filesystem::path folderpath)
{
	GetEmbededFiles().clear();
	s_basepath = folderpath;
	m_fileManager.IterateFolder(folderpath, m_codeGenerator, FileHandle);
}

void EmbedManager::Export(std::filesystem::path outputpath)
{
	std::filesystem::path embedspath = outputpath / "embeds";
	if (!std::filesystem::exists(embedspath))
	{
		try
		{
			std::filesystem::create_directories(embedspath);
		}
		catch (const std::filesystem::filesystem_error& ex)
		{
			MAGMA_ERROR("Error creating embeds directory: {0}", ex.what());
		}
	}

	for (auto& filepayload : m_codeGenerator.GetEmbededFiles())
	{
		if (!filepayload.include) continue;

		std::filesystem::path filepath = embedspath / filepayload.variableName;
		std::ofstream outfile(filepath.string() + ".h");
		if (!outfile.good())
		{
			MAGMA_ERROR("Could not export file '{0}'", filepath);
			continue;
		}
		// MAGMA_INFO("filepath: {0}", filepath);
		outfile << filepayload.embedcontent;
		outfile.close();
	}


	ServerClassPayload serverClassPayload = m_codeGenerator.GenerateServerClass();

	{
		std::ofstream headerfile(outputpath / "EmbedServer.h");
		if (!headerfile.good())
		{
			MAGMA_ERROR("Error creating a header file!");
		}
		headerfile << serverClassPayload.headercontent;
		headerfile.close();
	}

	{
		std::ofstream cppfile(outputpath / "EmbedServer.cpp");
		if (!cppfile.good())
		{
			MAGMA_ERROR("Error creating a cpp file!");
		}
		cppfile << serverClassPayload.cppcontent;
		cppfile.close();
	}

	{
		std::ofstream httprequestheaderfile(outputpath / "HttpRequest.h");
		if (!httprequestheaderfile.good())
		{
			MAGMA_ERROR("Error creating a HttpRequest.h file!");
		}
		httprequestheaderfile << HttpRequestHeaderEmbed;
		httprequestheaderfile.close();
	}
	{
		std::ofstream httprequestcppfile(outputpath / "HttpRequest.cpp");
		if (!httprequestcppfile.good())
		{
			MAGMA_ERROR("Error creating a HttpRequest.cpp file!");
		}
		httprequestcppfile << HttpRequestSourceEmbed;
		httprequestcppfile.close();
	}
}

// static callback function used to iterate through each file
void EmbedManager::FileHandle(std::filesystem::path filepath, std::vector<uint8_t> content, CodeGenerator& codeGenerator)
{
	// MAGMA_TRACE("{0}", filepath.filename().string());

	if (content.empty()) return;

	codeGenerator.GenerateEmbed(filepath, content,s_basepath);
}