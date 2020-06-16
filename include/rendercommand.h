#ifndef __RENDER_COMMAND__
#define __RENDER_COMMAND__ 1

namespace VC {

	class RenderCommand {

	public:

		virtual ~RenderCommand() {};

		virtual void Action() = 0;

	};

}

#endif // __RENDER_COMMAND__
