
#include <material.h>
#include <memory>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <logger.h>

using namespace VC;

static struct {
	std::unique_ptr<u32[]> ids;
	std::unique_ptr<std::string[]> vertex;
	std::unique_ptr< std::string[]> fragment;
}MaterialData;

void Material::Inicialize(u32 max_materials)
{
	MaterialData.vertex.reset(new std::string[max_materials]);
	MaterialData.fragment.reset(new std::string[max_materials]);
	MaterialData.ids.reset(new u32[max_materials]);
	for (u32 i = 0; i < max_materials; i++)
	{
		MaterialData.ids[i] = 0;
	}
}


void Material::setVertexShaderSource(std::string src)
{
	MaterialData.vertex[ID] = src;
}

void Material::setVertexShaderSource(const char* src)
{
	MaterialData.vertex[ID] = std::string(src);
}

void Material::setFragmentShaderSource(std::string src)
{
	MaterialData.fragment[ID] = src;
}

void Material::setFragmentShaderSource(const char* src)
{
	MaterialData.fragment[ID] = std::string(src);
}

void Material::LoadShadersFromFile(const char* vertexShaderPath, const char* fragmentShaderPath)
{

	setVertexShaderSource(SourceFromFile(vertexShaderPath));
	setFragmentShaderSource(SourceFromFile(fragmentShaderPath));

}

const char* Material::getVertexShaderSource()
{
	return MaterialData.vertex[ID].c_str();
}
const char* Material::getFragmentShaderSource()
{
	return MaterialData.fragment[ID].c_str();
}


u32 Material::getMaterialID()
{
	return MaterialData.ids[ID];
}
void Material::setMaterialID(u32 id)
{
	MaterialData.ids[ID] = id;
}

char* Material::SourceFromFile(const char* path)
{
	FILE* myFile = fopen(path, "rb");

	if (myFile == nullptr)
	{
		//printf("[ERROR] : Failed to load shader file from path (%s)\n", filePath);
		Logger::addMessage("Failed to load shader source from file");
		return nullptr;
	}
	else {
		fseek(myFile, 0, SEEK_END);

		long int fileSize = ftell(myFile);
		fseek(myFile, 0, SEEK_SET);

		char* code;
		code = (char*)malloc(fileSize * sizeof(char) + 1);
		code[fileSize] = '\0';

		fread(code, 1, fileSize, myFile);

		return code;

	}
}
