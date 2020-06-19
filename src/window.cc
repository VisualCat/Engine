
#include <window.h>
#include <GLEW/GL/glew.h>
#include <GLFW/glfw3.h>

#include <IMGUI/imgui_impl_glfw.h>
#include <IMGUI/imgui_impl_opengl3.h>

using namespace VC;

static GLFWwindow* window_;



s8 Window::Init() {

	if (!glfwInit())
		return -1;



	return 0;

}

void Window::CreateWindow(u32 width, u32 height, const char* title) {

#ifdef _GLFW_USE_OPENGL
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
#endif

	window_ = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!window_) {

		glfwTerminate();
		return;
	}


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	xMouse = width/2.0;
	yMouse = height/2.0;
	//TODO Check if we need to remove this
	glViewport(0, 0, width, height);

}

void Window::GetMouseInput() {
	glfwGetCursorPos(window_, &xMouse, &yMouse);
}

void Window::PollEvents() {
	
	glfwPollEvents();
	
}

void Window::SwapBuffers()
{

	glfwSwapBuffers(window_);
}

s32 VC::Window::ShouldClose()
{
	return glfwWindowShouldClose(window_);
}

void VC::Window::MakeCurrentContext()
{

#ifdef _GLFW_USE_OPENGL
	glfwMakeContextCurrent(window_);
	glewExperimental = GL_TRUE;
	glewInit();
	//TODO Check if we need to remove this
	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string

	
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window_, true);
	ImGui_ImplOpenGL3_Init("#version 330");
#endif

}

s8 Window::Terminate() {

	if (!window_)
	{
		glfwDestroyWindow(window_);
		glfwTerminate();
		return -1;
	}

	return 0;
}

void Window::ClearColor(float r, float g, float b, float a)
{
	//TODO this should be a command
	glClearColor(r,g,b,a);
}

void Window::Clear()
{
	ClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	//TODO this should be a command
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}
