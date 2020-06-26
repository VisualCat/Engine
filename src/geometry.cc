#include <geometry.h>
#include <memory>
#include <vector>

using namespace VC;

static struct {
  std::unique_ptr<u32[]> v_ids; //VerticesBuffer_ids
  std::unique_ptr<u32[]> e_ids; //ElementsBuffer_ids
  std::unique_ptr<std::vector<float>[]> vertices;
  std::unique_ptr<std::vector<float>[]> normals;
  std::unique_ptr<std::vector<float>[]> UVs;
	std::unique_ptr<std::vector<u32>[]> elements;
}GeometryData;

void Geometry::Inicialize(u32 max_geometries)
{
  GeometryData.vertices.reset(new std::vector<float>[max_geometries]);
  GeometryData.normals.reset(new std::vector<float>[max_geometries]);
  GeometryData.UVs.reset(new std::vector<float>[max_geometries]);

	GeometryData.elements.reset(new std::vector<u32>[max_geometries]);

	GeometryData.v_ids.reset(new u32[max_geometries]);
	for (u32 i = 0; i < max_geometries; i++)
	{
		GeometryData.v_ids[i] = 0;
	}

  GeometryData.e_ids.reset(new u32[max_geometries]);
  for (u32 i = 0; i < max_geometries; i++)
  {
    GeometryData.e_ids[i] = 0;
  }
}

void Geometry::CreatePrism(bool withUVs, float width, float height, float depth, float pivotOffsetX, float pivotOffsetY, float pivotOffsetZ) {
  float cubeRadius = 0.5f;

  width *= cubeRadius;
  width += pivotOffsetX * cubeRadius;

  height *= cubeRadius;
  height += pivotOffsetY * cubeRadius;

  depth *= cubeRadius;
  depth += pivotOffsetZ * cubeRadius;

  cubeRadius = height * 2.0f;

  std::vector<float> positions = {
    width, height, depth, //cubo front
    -width, height, depth,
    -width, -cubeRadius + height, depth,
    width, -cubeRadius + height, depth,

    -width, height, -depth,//Cubo back
    width, height, -depth,
    width, -cubeRadius + height, -depth,
    -width, -cubeRadius + height, -depth,

    width, height, -depth,//Cubo right
    width, height, depth,
    width, -cubeRadius + height, depth,
    width, -cubeRadius + height, -depth,

    -width, height, depth,//Cubo left
    -width, height, -depth,
    -width, -cubeRadius + height, -depth,
    -width, -cubeRadius + height, depth,


    width, height, -depth,//Cubo up
    -width, height, -depth,
    -width, height, depth,
    width, height, depth,

    width, -cubeRadius + height, depth,//Cubo down
    -width, -cubeRadius + height, depth,
    -width, -cubeRadius + height, -depth,
    width, -cubeRadius + height, -depth

  };

  std::vector<float> normals = {
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,

    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,

    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,

    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,

    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,

    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f
  };

  std::vector<unsigned int> indices = {
    0, 1, 2,
    2, 3, 0,

    4, 5, 6,
    6, 7, 4,

    8, 9, 10,
    10, 11, 8,

    12,13,14,
    14,15,12,

    16,17,18,
    18,19,16,

    20,21,22,
    22,23,20

  };

  std::vector<float> uvs = {
    1,1,
    1,1,
    1,1,
    1,1,
    1,1

  };

  u32 positionsArraySize = positions.size();
  setVertex(positions.data(), positionsArraySize);

  u32 normalsArraySize = normals.size();
  setNormals(normals.data(), normalsArraySize);

  u32 indicesArraySize = indices.size();
  setElements(indices.data(), indicesArraySize);

  if (withUVs)
  {
    u32 uvArraySize = uvs.size();
    setUVs(uvs.data(), uvArraySize);
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

u32 Geometry::getVertexSizeInBytes()
{
  return getNumVertex() * sizeof(float);
}

void Geometry::setNormals(float* normals, u32 num_normals)
{
  for (u32 i = 0; i < num_normals * 3; i++)
  {
    GeometryData.normals[ID].push_back(normals[i]);
  }
}

float* Geometry::getNormals()
{
  return GeometryData.normals[ID].data();
}

u32 Geometry::getNumNormals()
{
  return GeometryData.normals[ID].size();
}

u32 Geometry::getNormalsSizeInBytes()
{
  return getNumNormals() * sizeof(float);
}

void Geometry::setUVs(float* uvs, u32 num_uvs)
{
  for (u32 i = 0; i < num_uvs * 2; i++)
  {
    GeometryData.UVs[ID].push_back(uvs[i]);
  }
}

float* Geometry::getUVs()
{
  return GeometryData.UVs[ID].data();
}

u32 Geometry::getNumUVs()
{
  return GeometryData.UVs[ID].size();
}

u32 VC::Geometry::getUVsSizeInBytes()
{
  return getNumUVs() * sizeof(float);
}


void Geometry::setElements(u32* elements, u32 num_elements)
{
	for (u32 i = 0; i < num_elements; i++)
	{
		GeometryData.elements[ID].push_back(elements[i]);
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

u32 Geometry::getVerticesBufferID()
{
	return GeometryData.v_ids[ID];
}

void Geometry::setVerticesBufferID(u32 id)
{
	GeometryData.v_ids[ID] = id;
}

u32 VC::Geometry::getElementsBufferID()
{
  return GeometryData.e_ids[ID];
}

void VC::Geometry::setElementsBufferID(u32 id)
{
  GeometryData.e_ids[ID] = id;
}
