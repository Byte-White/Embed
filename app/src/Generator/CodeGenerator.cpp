#include "CodeGenerator.h"
#include <sstream>

void CodeGenerator::GenerateEmbed(std::filesystem::path filepath, std::vector<uint8_t> content)
{
	FilePayload filepayload;

	filepayload.filepath = filepath;

	std::string variablename = "file_" + filepath.relative_path().string();
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

	filepayload.embedcontent = ss.str();
	m_embededFiles.emplace_back(filepayload);
}
std::string CodeGenerator::GenerateServerClass()
{
	return std::string();
}