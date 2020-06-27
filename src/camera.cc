#include <camera.h>
#define M_PI 3.14159265358979323846264338327950288
#define kcameraSpeed 0.05f

using namespace VC;

float anglesToRadians(float degrees) {
	return (degrees * M_PI) / 180;
}

void Camera::init()
{
	cameraPos = Vector3(0.0f, 0.0f, 3.0f);
	//cameraFront = Vector3(0.0f, 0.0f, -1.0f);
	cameraUp = Vector3(0.0f, 1.0f, 0.0f);
	WorldUp = Vector3(0.0f, 1.0f, 0.0f);;
	yaw = -90.0f;
	pitch = 0.0f;
	roll = 0.0f;
	direction.x = cos(anglesToRadians(yaw)) * cos(anglesToRadians(pitch));
	direction.y = sin(anglesToRadians(pitch));
	direction.z = sin(anglesToRadians(yaw)) * cos(anglesToRadians(pitch));
	cameraFront = direction.Normalized();

	cameraRight = Vector3::CrossProduct(cameraFront, WorldUp).Normalized();

	firstMouse = true;
	view = Matrix4x4::LookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	projection = Matrix4x4::Projection(1.5707963268f, 1280.0f / 720.0f, 0.1f, 1000.0f);

}

void Camera::input(Window* window)
{

	if (window->getKeyPressed(Window::kVC_KEY_W))
	{
		cameraPos += (cameraFront) * kcameraSpeed;
	}
	if (window->getKeyPressed(Window::kVC_KEY_S))
	{
		cameraPos -= (cameraFront) * kcameraSpeed;
	}
	if (window->getKeyPressed(Window::kVC_KEY_A))
	{

		cameraPos -= cameraRight * kcameraSpeed;
	}
	if (window->getKeyPressed(Window::kVC_KEY_D))
	{
		cameraPos += cameraRight * kcameraSpeed;
	}

  if (window->getKeyPressed(Window::kVC_KEY_SPACE))
  {
    cameraPos += WorldUp * kcameraSpeed;
  }
  if (window->getKeyPressed(Window::kVC_KEY_LEFT_SHIFT))
  {
    cameraPos -= WorldUp * kcameraSpeed;
  }

	if (window->GetMousePressed(Window::KVC_MOUSE_KEY_RIGHT))
	{
		if (firstMouse)
		{
			lastX = window->xMouse;
			lastY = window->yMouse;
			firstMouse = false;
		}

		float xoffset = window->xMouse - lastX;
		float yoffset = window->yMouse - lastY;
		lastX = window->xMouse;
		lastY = window->yMouse;

		float sensitivity = 0.1f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch -= yoffset;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
		

		//cameraUp = Vector3::CrossProduct(cameraFront, cameraRight);
	}
	else {
		firstMouse = true;
	}
	

}


void Camera::update()
{

	cameraRight = Vector3::CrossProduct(cameraFront, WorldUp).Normalized();

	direction.x = cos(anglesToRadians(yaw)) * cos(anglesToRadians(pitch));
	direction.y = sin(anglesToRadians(pitch));
	direction.z = sin(anglesToRadians(yaw)) * cos(anglesToRadians(pitch));
	cameraFront = direction.Normalized();
	cameraUp = Vector3::CrossProduct(cameraRight, cameraFront).Normalized();


	view = Matrix4x4::LookAt(cameraPos, cameraPos + cameraFront, cameraUp);


}

