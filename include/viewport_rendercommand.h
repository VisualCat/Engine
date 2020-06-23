#ifndef __VIEWPORT_RENDER_COMMAND__
#define __VIEWPORT_RENDER_COMMAND__ 1

#include <rendercommand.h>
#include <platform_types.h>

namespace VC {

	class ViewportCommand : public RenderCommand {

	public:

		virtual ~ViewportCommand();
		ViewportCommand();

		virtual void Action() override;

		void setProperties(u32 width, u32 height, u32 x = 0, u32 y = 0);


	private:

		u32 x_;
		u32 y_;
		u32 width_;
		u32 height_;


	};

}

#endif // __VIEWPORT_RENDER_COMMAND__
