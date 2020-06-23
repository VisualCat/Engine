
#define kWindowWidth 1280
#define kWindowHeight 720

#define kmaxBuffers 200000
#define kmaxMaterials 200000

#include <app.h>

#include <GLEW/GL/glew.h>
#include <IMGUI/imgui_impl_glfw.h>
#include <IMGUI/imgui_impl_opengl3.h>

#include <geometry.h>
#include <material.h>
#include <clearwindow_rendercommand.h>
#include <object.h>

using namespace VC;

void App::Init()
{

	Geometry::Inicialize(kmaxBuffers);
	Material::Inicialize(kmaxMaterials);

	myWindow.Init();
	myWindow.CreateWindow(kWindowWidth, kWindowHeight, "Main Window");

	myWindow.MakeCurrentContext();

	
	const char* vertexShaderSource = R"(
		#version 330 core
		layout (location = 0) in vec3 aPos;
		void main()
		{
		   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
		}
	)";

	const char* fragmentShaderSource = R"(
		#version 330 core
		out vec4 FragColor;

		void main()
		{
			FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
		} 
	)";


	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};

	Material triangleMat{ 1 };
	Geometry triangleGeo{ 1 };
	
  triangleGeo.setVertex(vertices, 3);
  triangleMat.setVertexShader(vertexShaderSource);
  triangleMat.setFragmentShader(fragmentShaderSource);

  Object *triangle = new Object();
  triangle->setGeometry(&triangleGeo);
  triangle->setMaterial(&triangleMat);

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
	myWindow.PollEvents();
	myWindow.getKeyPressed(Window::kVC_KEY_SPACE);
}

void App::update()
{

}

void App::draw()
{

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	//ClearWindowCommand* cCommand = new ClearWindowCommand();
	//cCommand->setColor(0.8f, 0.8f, 0.8f);
	//comands_.push_back(cCommand);
	myWindow.Clear();



	for each (RenderCommand* com in comands_)
	{
		com->Action();
	}

  comands_.clear();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


	myWindow.SwapBuffers();
}


