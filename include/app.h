
#ifndef __VC_APP__
#define __VC_APP__ 1

#include <window.h>
#include <rendercommand.h>
#include <buffer_rendercommand.h>
#include <material_rendercommand.h>
#include <draw_rendercommand.h>
#include <vector>

namespace VC {

	class App {
	public:
		void Init();
		void Loop();
		void End();

	private:
		void input();
		void update();
		void draw();
		Window myWindow;
    std::vector<RenderCommand*> comands_;
	};


}

#endif
