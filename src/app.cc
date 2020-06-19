
#define kWindowWidth 1280
#define kWindowHeight 720

#define kmaxBuffers 200000
#define kmaxMaterials 200000

#include <app.h>

#include <GLEW/GL/glew.h>
#include <IMGUI/imgui_impl_glfw.h>
#include <IMGUI/imgui_impl_opengl3.h>

#include <buffer.h>
#include <material.h>

using namespace VC;

void App::Init()
{

	Buffer::Inicialize(kmaxBuffers);
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
	Buffer triangle{ 1 };
	BufferCommand* bComand = new BufferCommand();
	triangle.setVertex(vertices, 3);
	bComand->setBuffer(triangle.ID);
	triangleMat.setVertexShader(vertexShaderSource);
	triangleMat.setFragmentShader(fragmentShaderSource);
	MaterialCommand* mComand = new MaterialCommand();
	mComand->setMaterial(triangleMat.ID);

	DrawCommand* dCommand = new DrawCommand();
	dCommand->setBuffer(triangle.ID);

	comands_.push_back(bComand);
	comands_.push_back(mComand);
	comands_.push_back(dCommand);
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
	//bool demo = false;
	//ImGui::ShowDemoWindow(&demo);

	for each (RenderCommand* com in comands_)
	{
		com->Action();
	}
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


	myWindow.SwapBuffers();
}


