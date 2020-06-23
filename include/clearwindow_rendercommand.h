#ifndef __CLEAR_WINDOW_RENDER_COMMAND__
#define __CLEAR_WINDOW_RENDER_COMMAND__ 1

#include <rendercommand.h>
#include <platform_types.h>

namespace VC {

	class ClearWindowCommand : public RenderCommand {

	public:

		virtual ~ClearWindowCommand();
		ClearWindowCommand();

		virtual void Action() override;

		void setColor(float R, float G, float B);
		

	private:

		float color[3];
		//bool bClearColor;
		//bool bClearDepth;

	};

}

#endif // __CLEAR_WINDOW_RENDER_COMMAND__
