
#include <geometry.h>
#include <memory>
#include <vector>
#include <string>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <logger.h>

using namespace VC;
using namespace glm;

static struct {
  std::unique_ptr<u32[]> v_ids; //VerticesBuffer_ids
  std::unique_ptr<u32[]> e_ids; //ElementsBuffer_ids
  std::unique_ptr<std::vector<float>[]> vertices;
  std::unique_ptr<std::vector<float>[]> normals;
  std::unique_ptr<std::vector<float>[]> UVs;
  std::unique_ptr<std::vector<float>[]> tangents;
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

bool Geometry::LoadOBJ(const char* filepath, bool loadTangents)
{
  std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;

  std::vector<vec3> temp_vertices;
  std::vector<vec2> temp_uvs;
  std::vector<vec3> temp_normals;

  std::vector<vec3> outPosition;
  std::vector<vec3> outNormal;
  std::vector<vec2> outUV;
  std::vector<vec3> outTangent;


  FILE* file = fopen(filepath, "r");
  if (file == NULL) {
    Logger::addMessage("Could not load OBJ. File not found or corrupt.");
    return false;
  }

  while (1) {

    char lineHeader[128];
    // read the first word of the line
    int res = fscanf(file, "%s", lineHeader);
    if (res == EOF) {// EOF = End Of File. Quit the loop.
      break;
    }
    else
    {
      if (strcmp(lineHeader, "v") == 0)
      {
        vec3 vertex;
        fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
        temp_vertices.push_back(vertex);
      }
      else if (strcmp(lineHeader, "vt") == 0)
      {
        vec2 uv;
        fscanf(file, "%f %f\n", &uv.x, &uv.y);
        temp_uvs.push_back(uv);
      }
      else if (strcmp(lineHeader, "vn") == 0) {
        vec3 normal;
        fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
        temp_normals.push_back(normal);
      }
      else if (strcmp(lineHeader, "f") == 0) {
        std::string vertex1, vertex2, vertex3;
        unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
        int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
        if (matches != 9) {
          printf("File can't be read by our simple parser : ( Try exporting with other options\n");
          return false;
        }
        vertexIndices.push_back(vertexIndex[0]);
        vertexIndices.push_back(vertexIndex[1]);
        vertexIndices.push_back(vertexIndex[2]);
        uvIndices.push_back(uvIndex[0]);
        uvIndices.push_back(uvIndex[1]);
        uvIndices.push_back(uvIndex[2]);
        normalIndices.push_back(normalIndex[0]);
        normalIndices.push_back(normalIndex[1]);
        normalIndices.push_back(normalIndex[2]);
      }
    }

  }//Finalize read file
  //Order Vertex, normal and uv vectors with indexes

  for (unsigned int i = 0; i < vertexIndices.size(); ++i)
  {
    unsigned int vertexIndex = vertexIndices[i];
    vec3 vert = temp_vertices[vertexIndex - 1];
    outPosition.push_back(vert);
  }

  for (unsigned int i = 0; i < normalIndices.size(); ++i)
  {
    unsigned int normIndex = normalIndices[i];
    vec3 norm = temp_normals[normIndex - 1];
    outNormal.push_back(norm);
  }

  for (unsigned int i = 0; i < uvIndices.size(); ++i)
  {
    unsigned int uvIndex = uvIndices[i];
    vec2 uv = temp_uvs[uvIndex - 1];
    outUV.push_back(uv);
  }



  const unsigned int positionsNumOfFloats = outPosition.size() * 3;
  const unsigned int normalsNumOfFloats = outNormal.size() * 3;
  const unsigned int uvNumOfFloats = outUV.size() * 2;
  unsigned int tangentNumOfFloats;
  const unsigned int indicesNumOfFloats = positionsNumOfFloats / 2;

  
  float* tangents = nullptr;
  if (loadTangents) {
    for (unsigned int i = 0; i < outPosition.size(); i += 3)
    {

      vec3 tangent;

      vec3 pos1 = outPosition[i];
      vec3 pos2 = outPosition[i + 1];
      vec3 pos3 = outPosition[i + 2];

      vec2 uv1 = outUV[i];
      vec2 uv2 = outUV[i + 1];
      vec2 uv3 = outUV[i + 2];

      vec3 edge1 = pos2 - pos1;
      vec3 edge2 = pos3 - pos1;

      vec2 deltaUV1 = uv2 - uv1;
      vec2 deltaUV2 = uv3 - uv1;

      float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);

      tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
      tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
      tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
      //tangent = tangent.Normalized();

      outTangent.push_back(tangent);
      outTangent.push_back(tangent);
      outTangent.push_back(tangent);

    }
    tangentNumOfFloats = outTangent.size() * 3;

    tangents = (float*)malloc(tangentNumOfFloats * sizeof(float));

    for (unsigned int i = 0; i < outTangent.size(); i++)
    {
      tangents[i * 3] = outTangent[i].x;
      tangents[i * 3 + 1] = outTangent[i].y;
      tangents[i * 3 + 2] = outTangent[i].z;

    }

    setTangents(tangents, outTangent.size());

  }

  float* positions = (float*)malloc(positionsNumOfFloats * sizeof(float));
  float* normals = (float*)malloc(normalsNumOfFloats * sizeof(float));
  float* UVs = (float*)malloc(uvNumOfFloats * sizeof(float));
  u32* indices = (u32*)malloc(indicesNumOfFloats * sizeof(u32));

  for (unsigned int i = 0; i < outPosition.size(); ++i)
  {
    positions[i * 3] = outPosition[i].x;
    positions[i * 3 + 1] = outPosition[i].y;
    positions[i * 3 + 2] = outPosition[i].z;
  }

  for (unsigned int i = 0; i < outNormal.size(); ++i)
  {
    normals[i * 3] = outNormal[i].x;
    normals[i * 3 + 1] = outNormal[i].y;
    normals[i * 3 + 2] = outNormal[i].z;
  }

  

  for (unsigned int i = 0; i < outUV.size(); ++i)
  {
    UVs[i * 2] = outUV[i].x;
    UVs[i * 2 + 1] = outUV[i].y;
  }

  for (unsigned int i = 0; i < indicesNumOfFloats; ++i)
  {
    indices[i] = i;
  }

  setVertex(positions, outPosition.size());
  setNormals(normals, outNormal.size());
  setUVs(UVs, outUV.size());
  setElements(indices, indicesNumOfFloats);
 
  return true;
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
  setVertex(positions.data(), positionsArraySize/3);

  u32 normalsArraySize = normals.size();
  setNormals(normals.data(), normalsArraySize/3);

  if (withUVs)
  {
    u32 uvArraySize = uvs.size();
    setUVs(uvs.data(), uvArraySize/2);
  }

  u32 indicesArraySize = indices.size();
  setElements(indices.data(), indicesArraySize);


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

void Geometry::setTangents(float* tangents, u32 num_tangents)
{
  for (u32 i = 0; i < num_tangents * 3; i++)
  {
    GeometryData.tangents[ID].push_back(tangents[i]);
  }
}

float* Geometry::getTangents()
{
  return GeometryData.tangents[ID].data();
}

u32 Geometry::getNumTangents()
{
  return GeometryData.tangents[ID].size();
}

u32 VC::Geometry::getTangentsSizeInBytes()
{
  return getNumTangents() * sizeof(float);
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
