#include <geometry.h>
#include <memory>
#include <vector>

using namespace VC;

static struct {
	std::unique_ptr<u32[]> ids;
	std::unique_ptr<std::vector<float>[]> vertices;
	std::unique_ptr<std::vector<u32>[]> elements;
}GeometryData;

void Geometry::Inicialize(u32 max_geometries)
{
	GeometryData.vertices.reset(new std::vector<float>[max_geometries]);
	GeometryData.elements.reset(new std::vector<u32>[max_geometries]);
	GeometryData.ids.reset(new u32[max_geometries]);
	for (u32 i = 0; i < max_geometries; i++)
	{
		GeometryData.ids[i] = 0;
	}
}

void Geometry::setVertex(float* vertices, u32 num_vertices)
{
	for (u32 i = 0; i < num_vertices * 3; i++)
	{
		GeometryData.vertices[ID].push_back(vertices[i]);
	}
	
}


float* Geometry::getVertex()
{
	return GeometryData.vertices[ID].data();
}
u32 Geometry::getNumVertex() 
{
	return GeometryData.vertices[ID].size();
}


void Geometry::setElements(u32* elements, u32 num_elements)
{
	for (u32 i = 0; i < num_elements; i++)
	{
		GeometryData.vertices[ID].push_back(elements[i]);
	}
}


u32* Geometry::getElements()
{
	return GeometryData.elements[ID].data();
}
u32 Geometry::getNumElements()
{
	return GeometryData.elements[ID].size();
}

u32 Geometry::getGeometryID()
{
	return GeometryData.ids[ID];
}

void Geometry::setGeometryID(u32 id)
{
	GeometryData.ids[ID] = id;
}
