#include "CodeGenerator.h"
#include <sstream>

void CodeGenerator::GenerateEmbed(std::filesystem::path filepath, std::vector<uint8_t> content,std::filesystem::path basepath)
{
	FilePayload filepayload;

    filepayload.filepath = filepath;
    filepayload.relativepath = std::filesystem::relative(filepath, basepath);

	std::string variablename = "file_" + filepayload.relativepath.string();
	std::replace_if(variablename.begin(), variablename.end(), [](char ch) {
		return ch == '.' || ch == ' ' || ch == '-' || ch == '-' || ch == '/' || ch == '\\';
		}, '_');
	filepayload.variableName = variablename;

	std::stringstream ss;
	ss << "uint8_t " << variablename << "[" << content.size() << "] = {";
	for (int i = 0; i < content.size(); i++)
	{
		if (i % 10 == 0) ss << "\n"; // for readability

		ss << static_cast<int>(content[i]);
		if (i != content.size() - 1) ss << ",";
	}
	ss << "};";
    filepayload.filesize = content.size();
	filepayload.embedcontent = ss.str();
	m_embeddedFiles.emplace_back(filepayload);
}

ServerClassPayload CodeGenerator::GenerateServerClass()
{
    ServerClassPayload payload;

    payload.headercontent = GenerateHeaderFileContent();

    payload.cppcontent = GenerateSourceFileContent();

    return payload;
}

std::string CodeGenerator::GenerateHeaderFileContent()
{
    std::stringstream headerStream;
    HeaderGenerator::AddClassBeginning(headerStream, m_embeddedFiles);

    HeaderGenerator::AddHandleFunctionsDeclarations(headerStream, m_embeddedFiles);

    HeaderGenerator::AddClassEnding(headerStream, m_embeddedFiles);

    return headerStream.str();
}

std::string CodeGenerator::GenerateSourceFileContent()
{
    std::stringstream sourceStream;
    SourceGenerator::AddIncludes(sourceStream, m_embeddedFiles);

    SourceGenerator::AddBeginServerFunction(sourceStream, m_embeddedFiles);

    SourceGenerator::AddHandleClientFunction(sourceStream, m_embeddedFiles);

    SourceGenerator::AddHandleFunctionsImplementations(sourceStream, m_embeddedFiles);

    return sourceStream.str();
}


void HeaderGenerator::AddClassBeginning(std::stringstream& headerStream, const FilePayloadsVec& embeddedFiles)
{
    headerStream 
        << "#include \"HttpRequest.h\"\n\n"
        << "class EmbedServer\n{\npublic:\n"
        << "\tEmbedServer(int port) : m_server(port) {}\n"
        << "\tvoid begin();\n"
        << "\tvoid handleClient();\n";
}

void HeaderGenerator::AddClassEnding(std::stringstream& headerStream, const FilePayloadsVec& embeddedFiles)
{
    headerStream << "private:\n\tWiFiServer m_server;\n\tHttpRequest m_request;\n};";
}


void HeaderGenerator::AddHandleFunctionsDeclarations(std::stringstream& headerStream, const FilePayloadsVec& embeddedFiles)
{
    for (auto& file : embeddedFiles)
    {
        if (!file.include) continue;
        headerStream << "\tvoid handle" << file.variableName << "(WiFiClient& client);\n";
    }
}


void SourceGenerator::AddIncludes(std::stringstream& sourceStream, const FilePayloadsVec& embeddedFiles)
{
    sourceStream << "#include \"EmbedServer.h\"\n";

    for (auto& file : embeddedFiles)
    {
        if (!file.include) continue;

        sourceStream << "#include \"embeds/" << file.variableName << ".h\"\n";
    }
}

void SourceGenerator::AddBeginServerFunction(std::stringstream& sourceStream, const FilePayloadsVec& embeddedFiles)
{
    sourceStream 
        << "\n"
        << "void EmbedServer::begin()\n"
        <<"{\n"
        << "\tm_server.begin();\n"
        <<"}\n";
}


void SourceGenerator::AddHandleClientFunction(std::stringstream& sourceStream, const FilePayloadsVec& embeddedFiles)
{
    sourceStream << "\n"
        << "void EmbedServer::handleClient()\n"
        << "{\n"
        << "\tWiFiClient client = m_server.available();\n"
        << "\tif (client)\n"
        << "\t{\n"
        << "\t\tm_request.reset();\n"
        << "\t\tm_request.process(client);\n"
        ;
    int fileindex = 0;
    for (auto& file : embeddedFiles)
    {
        if (!file.include) continue;

        std::string relativePathString = file.relativepath.string();
        std::replace(relativePathString.begin(), relativePathString.end(), '\\', '/');

        sourceStream << "\t\t" << (fileindex != 0 ? "else " : "") << "if(m_request.getMethod() == \"GET\" && m_request.getRequestedResource() == \"/" << relativePathString << "\")\n"
            << "\t\t{\n"
            << "\t\t\thandle" << file.variableName << "(client);\n"
            << "\t\t}\n";

        fileindex++;
    }
    sourceStream << "\t}\n"
        << "\tclient.stop();\n"
        << "}\n";
}

void SourceGenerator::AddHandleFunctionsImplementations(std::stringstream& sourceStream, const FilePayloadsVec& embeddedFiles)
{
    for (auto& file : embeddedFiles)
    {
        if (!file.include) continue;

        sourceStream << "void EmbedServer::handle" << file.variableName << "(WiFiClient& client)\n{\n";
        sourceStream << "client.write(" << file.variableName
            << ",sizeof(" << file.variableName << "));\n"; // no need to use file.filesize because sizeof can get it instead.
        sourceStream << "}\n\n";
    }
}