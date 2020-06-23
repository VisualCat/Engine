#ifndef __VC_GEOMETRY__
#define __VC_GEOMETRY__ 1

#include <platform_types.h>

namespace VC {

	class Geometry
	{
	public:

		static void Inicialize(u32 max_geometries);

		void setVertex(float* vertices, u32 num_vertices);
		float* getVertex();
		u32 getNumVertex();

		void setElements(u32* elements, u32 num_elements);
		u32* getElements();
		u32 getNumElements();
		


		u32 getGeometryID();
		void setGeometryID(u32 id);


		u32 ID;
	};

}


#endif // __VC_BUFFER__
