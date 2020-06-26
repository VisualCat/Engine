#ifndef __VC_GEOMETRY__
#define __VC_GEOMETRY__ 1

#include <platform_types.h>
#include <vector>

namespace VC {

	class Geometry
	{
	public:

		static void Inicialize(u32 max_geometries);

    //Dimensions modifiers go from 0.0f to 1.0f
    void CreatePrism(bool withUVs = false, float width = 1.0f, float height = 1.0f, float depth = 1.0f,
      float pivotOffsetX = 0.0f, float pivotOffsetY = 0.0f, float pivotOffsetZ = 0.0f);

		void setVertex(float* vertices, u32 num_vertices);
		float* getVertex();
    u32 getNumVertex();
    u32 getVertexSizeInBytes();

    void setNormals(float* normals, u32 num_normals);
    float* getNormals();
    u32 getNumNormals();
    u32 getNormalsSizeInBytes();

    void setUVs(float* uvs, u32 num_uvs);
    float* getUVs();
    u32 getNumUVs();
    u32 getUVsSizeInBytes();

		void setElements(u32* elements, u32 num_elements);
		u32* getElements();
		u32 getNumElements();
		


		u32 getVerticesBufferID();
		void setVerticesBufferID(u32 id);

    u32 getElementsBufferID();
    void setElementsBufferID(u32 id);


		u32 ID;
	};

}


#endif // __VC_BUFFER__
