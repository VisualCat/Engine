#include <camera.h>

using namespace VC;

void Camera::init()
{
	cameraPos = Vector3(0.0f, 0.0f, 3.0f);
	cameraFront = Vector3(0.0f, 0.0f, -1.0f);
	cameraUp = Vector3(0.0f, 1.0f, 0.0f);
}

void Camera::update()
{
	view = Matrix4x4::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}
