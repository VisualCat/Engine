#include <material.h>
#include <memory>
#include <string>

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


void Material::setVertexShader(std::string src)
{
	MaterialData.vertex[ID] = src;
	//MaterialData.vertex[ID].copy(src.c_str());
}

void Material::setFragmentShader(std::string src)
{
	MaterialData.fragment[ID] = src;
}

const char* Material::getVertexShader()
{
	return MaterialData.vertex[ID].c_str();
}
const char* Material::getFragmentShader()
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
