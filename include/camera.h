#ifndef __VC_CAMERA__
#define __VC_CAMERA__ 1

#include <vector_3.h>
#include <matrix_4.h>
#include <window.h>

namespace VC {

	class Camera
	{
	public:
		Camera()
		{

		}

		~Camera()
		{

		}
		void init();
		void input(Window* window);
		void update();

		Vector3 cameraPos;
		Vector3 cameraFront;
		Vector3 cameraUp;

		Vector3 direction;

		Matrix4x4 view;
		Matrix4x4 projection;

		float yaw;
		float pitch;
		float roll;

	private:
		
		float lastX;
		float lastY;
		bool firstMouse;

	};

}


#endif