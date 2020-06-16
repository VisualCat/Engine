
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


	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};

	
	BufferCommand* bComand = new BufferCommand();
	bComand->SetVertices(vertices,3);
	MaterialCommand* mComand = new MaterialCommand();
	comands_.push_back(bComand);
	comands_.push_back(mComand);
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

	for each (RenderCommand* com in comands_)
	{
		com->Action();
	}

	myWindow.SwapBuffers();
}


