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
	m_embededFiles.emplace_back(filepayload);
}
ServerClassPayload CodeGenerator::GenerateServerClass()
{
    ServerClassPayload payload;

    std::stringstream headerStream;
    headerStream << "#include <WiFi.h>\n\n"
        << "class EmbedServer\n{\npublic:\n"
        << "\tEmbedServer(int port) : m_server(port) {}\n"
        << "\tvoid handleClient();\n";
    for (auto& file : m_embededFiles)
    {
        headerStream << "\tvoid handle" << file.variableName << "(WiFiClient& client);\n";
    }
    headerStream << "private:\n\tWiFiServer m_server;\n\tString m_header;\n};";

    payload.headercontent = headerStream.str();

    std::stringstream sourceStream;
    sourceStream << "#include \"EmbedServer.h\"\n";

    for (auto& file : m_embededFiles)
    {
        sourceStream << "#include \"embeds/" << file.variableName << ".h\"\n";
    }
    sourceStream << "\n"
        << "void EmbedServer::handleClient()\n"
        << "{\n"
        << "\tWiFiClient client = m_server.available();\n"
        << "\tif (client)\n"
        << "\t{\n"
        << "\t\twhile(client.available())\n"
        << "\t\t{\n"
        << "\t\t\tchar c = client.read();\n"
        << "\t\t\tm_header += c;\n"
        << "\t\t}\n";
    int fileindex = 0;
    for (auto& file : m_embededFiles)
    {
        std::string relativePathString = file.relativepath.string();
        std::replace(relativePathString.begin(), relativePathString.end(), '\\', '/');

        sourceStream << "\t\t" << (fileindex != 0 ? "else " : "") << "if(m_header.indexOf(\"GET /" << relativePathString << " \") >= 0)\n"
            << "\t\t{\n"
            << "\t\t\thandle" << file.variableName << "(client);\n"
            << "\t\t}\n";
        
        fileindex++;
    }

    sourceStream << "\t}\n"
                << "}\n";

    for (auto& file : m_embededFiles)
    {
        sourceStream << "void EmbedServer::handle" << file.variableName << "(WiFiClient& client)\n{\n";
        sourceStream << "client.write(" << file.variableName 
                    << ",sizeof(" << file.variableName <<"));\n"; // no need to use file.filesize because sizeof can get it instead.
        sourceStream << "}\n\n";
    }

    payload.cppcontent = sourceStream.str();

    return payload;
}