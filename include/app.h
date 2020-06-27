
#ifndef __VC_APP__
#define __VC_APP__ 1

#include <window.h>

#include <rendercommand.h>
#include <buffer_rendercommand.h>
#include <material_rendercommand.h>
#include <draw_rendercommand.h>

#include <object.h>
#include <cordinator.h>
#include <vector>
#include <render_system.h>
#include <wavemovement_system.h>
#include <camera.h>
#include <chrono>

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
    void ImGuiDraw();

		Window window_;
		std::vector<RenderCommand*> commands_;
		std::vector<Object*> objectsInScene_;
		std::vector<u32> entities_;
		Camera camera_;
		Coordinator cordinator_;
		std::shared_ptr<RenderSystem> rendersys_;
		std::shared_ptr<WaveMovementSystem> wavemovementsys_;
		std::chrono::time_point<std::chrono::system_clock> start_time;
	};


}

#endif
