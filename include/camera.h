#ifndef __VC_CAMERA__
#define __VC_CAMERA__ 1

#include <vector_3.h>
#include <matrix_4.h>

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
		void update();

		Vector3 cameraPos;
		Vector3 cameraFront;
		Vector3 cameraUp;


	private:
		Matrix4x4 view;
		


	};

}


#endif