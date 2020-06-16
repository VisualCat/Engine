
#define kWindowWidth 1280
#define kWindowHeight 720

#include <app.h>

#include <GLEW/GL/glew.h>
#include <IMGUI/imgui_impl_glfw.h>
#include <IMGUI/imgui_impl_opengl3.h>

using namespace VC;

void App::Init()
{
	myWindow.Init();
	myWindow.CreateWindow(kWindowWidth, kWindowHeight, "Main Window");

	myWindow.MakeCurrentContext();

}

void App::Loop()
{

	while (!myWindow.ShouldClose())
	{
		input();
		update();
		draw();
	}

}

void App::End()
{

	myWindow.Terminate();

}

void App::input()
{

}

void App::update()
{

	myWindow.PollEvents();
	

}

void App::draw()
{

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	myWindow.Clear();
	bool demo = true;
	ImGui::ShowDemoWindow(&demo);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	myWindow.SwapBuffers();
}


