
#ifndef __VC_APP__
#define __VC_APP__ 1

#include <window.h>
#include <rendercommand.h>
#include <buffer_rendercommand.h>
#include <material_rendercommand.h>
#include <draw_rendercommand.h>
#include <object.h>
#include <vector>

#include <camera.h>

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
		std::vector<RenderCommand*> commands_;
		std::vector<Object*> objectsInScene_;
		Camera camera;
	};


}

#endif
