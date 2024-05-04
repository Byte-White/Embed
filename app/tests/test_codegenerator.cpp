#define CATCH_CONFIG_MAIN
#include "catch2/catch_test_macros.hpp"
#include "Generator/CodeGenerator.h"



TEST_CASE("FilePayload - Correct filepath", "[code generation]")
{
	CodeGenerator codeGenerator;
	std::vector<uint8_t> exampleData = { 0x19,0x28,0x37,0x46 };
	const char* filePath = "D:/ExamplePath/MyProject/res/exampleFile.bin";
	const char* basePath = "D:/ExamplePath/MyProject/res";
	codeGenerator.GenerateEmbed(filePath, exampleData, basePath);
	
	auto embeds = codeGenerator.GetEmbededFiles();

	
	REQUIRE(embeds[0].filepath == filePath);
}


TEST_CASE("FilePayload - Correct relative filepath", "[code generation]")
{
	CodeGenerator codeGenerator;
	std::vector<uint8_t> exampleData = { 0x19,0x28,0x37,0x46 };
	const char* filePath = "D:/ExamplePath/MyProject/res/exampleFile.bin";
	const char* basePath = "D:/ExamplePath/MyProject/res";
	codeGenerator.GenerateEmbed(filePath, exampleData, basePath);

	auto embeds = codeGenerator.GetEmbededFiles();

	REQUIRE(embeds[0].relativepath == "exampleFile.bin");
}


TEST_CASE("FilePayload - Correct variable name", "[code generation]")
{
	CodeGenerator codeGenerator;
	std::vector<uint8_t> exampleData = { 0x19,0x28,0x37,0x46 };
	const char* filePath = "D:/ExamplePath/MyProject/res/exampleFile.bin";
	const char* basePath = "D:/ExamplePath/MyProject/res";
	codeGenerator.GenerateEmbed(filePath, exampleData, basePath);
	
	auto embeds = codeGenerator.GetEmbededFiles();


	REQUIRE(embeds[0].variableName == "file_exampleFile_bin");
}


TEST_CASE("FilePayload - Correct file size", "[code generation]")
{
	CodeGenerator codeGenerator;
	std::vector<uint8_t> exampleData = { 0x19,0x28,0x37,0x46 };
	const char* filePath = "D:/ExamplePath/MyProject/res/exampleFile.bin";
	const char* basePath = "D:/ExamplePath/MyProject/res";
	codeGenerator.GenerateEmbed(filePath, exampleData, basePath);
	
	auto embeds = codeGenerator.GetEmbededFiles();


	REQUIRE(embeds[0].filesize == exampleData.size());
}


TEST_CASE("FilePayload - Correct embed content", "[code generation]")
{
	CodeGenerator codeGenerator;
	std::vector<uint8_t> exampleData = { 0x19,0x28,0x37,0x46 };
	const char* filePath = "D:/ExamplePath/MyProject/res/exampleFile.bin";
	const char* basePath = "D:/ExamplePath/MyProject/res";
	codeGenerator.GenerateEmbed(filePath, exampleData, basePath);

	auto embeds = codeGenerator.GetEmbededFiles();
	
	std::string expectedEmbedContent = R"(uint8_t file_exampleFile_bin[4] = {
25,40,55,70};)";

	REQUIRE(embeds[0].embedcontent == expectedEmbedContent);
}