#ifndef __DRAW_RENDER_COMMAND__
#define __DRAW_RENDER_COMMAND__ 1

#include <rendercommand.h>
#include <platform_types.h>
#include <geometry.h>

namespace VC {

	class DrawCommand : public RenderCommand {

	public:

		virtual ~DrawCommand();
		DrawCommand();

		virtual void Action() override;

		void setGeometry(u32 id);

	private:

    Geometry geometry_;



	};

}

#endif // __DRAW_RENDER_COMMAND__
