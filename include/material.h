#ifndef __VC_MATERIAL__
#define __VC_MATERIAL__ 1

#include <platform_types.h>
#include <string>

namespace VC {

	class Material
	{
	public:

		static void Inicialize(u32 max_materials);

		void setVertexShader(std::string src);
		void setFragmentShader(std::string src);
		
		const char* getVertexShader();
		const char* getFragmentShader();


		u32 getMaterialID();
		void setMaterialID(u32 id);


		u32 ID;
	};

}


#endif // __VC_MATERIAL__
