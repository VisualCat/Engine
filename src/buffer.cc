#include <buffer.h>
#include <memory>
#include <vector>

using namespace VC;

static struct {
	std::unique_ptr<u32[]> ids;
	std::unique_ptr<std::vector<float>[]> vertices;
	std::unique_ptr<std::vector<u32>[]> elements;
}BufferData;

void Buffer::Inicialize(u32 max_buffers)
{
	BufferData.vertices.reset(new std::vector<float>[max_buffers]);
	BufferData.elements.reset(new std::vector<u32>[max_buffers]);
	BufferData.ids.reset(new u32[max_buffers]);
	for (u32 i = 0; i < max_buffers; i++)
	{
		BufferData.ids[i] = 0;
	}
}

void Buffer::setVertex(float* vertices, u32 num_vertices)
{
	for (u32 i = 0; i < num_vertices * 3; i++)
	{
		BufferData.vertices[ID].push_back(vertices[i]);
	}
	
}


float* Buffer::getVertex()
{
	return BufferData.vertices[ID].data();
}
u32 Buffer::getNumVertex() 
{
	return BufferData.vertices[ID].size();
}


void Buffer::setElements(u32* elements, u32 num_elements)
{
	for (u32 i = 0; i < num_elements; i++)
	{
		BufferData.vertices[ID].push_back(elements[i]);
	}
}


u32* Buffer::getElements()
{
	return BufferData.elements[ID].data();
}
u32 Buffer::getNumElements()
{
	return BufferData.elements[ID].size();
}

u32 Buffer::getBufferID()
{
	return BufferData.ids[ID];
}

void Buffer::setBufferID(u32 id)
{
	BufferData.ids[ID] = id;
}
