#ifndef __VC_MATERIAL__
#define __VC_MATERIAL__ 1

#include <platform_types.h>
#include <string>

namespace VC {

	class Material
	{
	public:

		static void Inicialize(u32 max_materials);

		void setVertexShaderSource(std::string src);
		void setVertexShaderSource(const char* src);

		void setFragmentShaderSource(std::string src);
		void setFragmentShaderSource(const char* src);

		void LoadShadersFromFile(const char* vertexShaderPath, const char* fragmentShaderPath);
		
		const char* getVertexShaderSource();
		const char* getFragmentShaderSource();


		u32 getMaterialID();
		void setMaterialID(u32 id);


		u32 ID;

	private:
		char* SourceFromFile(const char* path);

	};

}


#endif // __VC_MATERIAL__
