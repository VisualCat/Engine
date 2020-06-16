
#ifndef __VC_APP__
#define __VC_APP__ 1

#include <window.h>

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

	};


}

#endif
