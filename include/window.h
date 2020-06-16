
#ifndef __VC_WINDOW__
#define __VC_WINDOW__ 1

#include <platform_types.h>
#include "imgui.h"

namespace VC {

	class Window {

	public:

		s8 Init();
		void CreateWindow(u32 width, u32 height, const char* title);

		void GetMouseInput();
		void PollEvents();
		void SwapBuffers();
		s32 ShouldClose();
		void MakeCurrentContext();
		s8 Terminate();

		//RENDER
		void ClearColor(float r, float g, float b, float a);
		void Clear();

	private:
		double xMouse;
		double yMouse;

	};

}

#endif