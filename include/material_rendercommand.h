#ifndef __MATERIAL_RENDER_COMMAND__
#define __MATERIAL_RENDER_COMMAND__ 1

#include <rendercommand.h>
#include <platform_types.h>
#include <material.h>

namespace VC {

	class MaterialCommand : public RenderCommand {

	public:

		virtual ~MaterialCommand();
		MaterialCommand();

		virtual void Action() override;

		void setMaterial(u32 id);

	private:

		Material material;



	};

}

#endif // __RENDER_COMMAND__
