#ifndef __MATERIAL_RENDER_COMMAND__
#define __MATERIAL_RENDER_COMMAND__ 1

#include <rendercommand.h>
#include <platform_types.h>

namespace VC {

	class MaterialCommand : public RenderCommand {

	public:

		virtual ~MaterialCommand();
		MaterialCommand();

		virtual void Action() override;


	private:




	};

}

#endif // __RENDER_COMMAND__
