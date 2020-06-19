#ifndef __DRAW_RENDER_COMMAND__
#define __DRAW_RENDER_COMMAND__ 1

#include <rendercommand.h>
#include <platform_types.h>
#include <buffer.h>

namespace VC {

	class DrawCommand : public RenderCommand {

	public:

		virtual ~DrawCommand();
		DrawCommand();

		virtual void Action() override;

		void setBuffer(u32 id);

	private:

		Buffer buffer_;



	};

}

#endif // __DRAW_RENDER_COMMAND__
