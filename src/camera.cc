#include <camera.h>

using namespace VC;

void Camera::init()
{
	cameraPos = Vector3(0.0f, 0.0f, 3.0f);
	cameraFront = Vector3(0.0f, 0.0f, -1.0f);
	cameraUp = Vector3(0.0f, 1.0f, 0.0f);
	projection = Matrix4x4::Projection(1.5707963268f, 1280.0f / 720.0f, 0.1f, 100.0f);
}

void Camera::update()
{
	view = Matrix4x4::LookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}
