
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

using namespace VC;

void App::Init()
{

	Geometry::Inicialize(kmaxBuffers);
	Material::Inicialize(kmaxMaterials);

	window_.Init();
	window_.CreateWindow(kWindowWidth, kWindowHeight, "Main Window");

	window_.MakeCurrentContext();
	camera_.init();

	
	const char* vertexShaderSource = R"(
		#version 330 core

		layout (location = 0) in vec3 aPos;

    uniform mat4 u_v_matrix;
    uniform mat4 u_p_matrix;
    uniform mat4 u_m_matrix;

    void main()
		{

           
           mat4 mvp = u_p_matrix * u_v_matrix * u_m_matrix;
		   gl_Position = mvp * vec4(aPos.x, aPos.y, aPos.z, 1.0);
		}
	)";

	const char* fragmentShaderSource = R"(
		#version 330 core
		out vec4 FragColor;

		void main()
		{
			FragColor = vec4(1.0, 0.5, 0.2, 1.0);
		} 
	)";


  float vertices[] = {
        -0.5f, -0.5f, -0.5f, 
         0.5f, -0.5f, -0.5f, 
         0.5f,  0.5f, -0.5f, 
         0.5f,  0.5f, -0.5f, 
        -0.5f,  0.5f, -0.5f, 
        -0.5f, -0.5f, -0.5f, 

        -0.5f, -0.5f,  0.5f, 
         0.5f, -0.5f,  0.5f, 
         0.5f,  0.5f,  0.5f, 
         0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f,  0.5f, 
        -0.5f, -0.5f,  0.5f, 

        -0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f, -0.5f, 
        -0.5f, -0.5f, -0.5f, 
        -0.5f, -0.5f, -0.5f, 
        -0.5f, -0.5f,  0.5f, 
        -0.5f,  0.5f,  0.5f, 

         0.5f,  0.5f,  0.5f, 
         0.5f,  0.5f, -0.5f, 
         0.5f, -0.5f, -0.5f, 
         0.5f, -0.5f, -0.5f, 
         0.5f, -0.5f,  0.5f, 
         0.5f,  0.5f,  0.5f, 

        -0.5f, -0.5f, -0.5f, 
         0.5f, -0.5f, -0.5f, 
         0.5f, -0.5f,  0.5f, 
         0.5f, -0.5f,  0.5f, 
        -0.5f, -0.5f,  0.5f, 
        -0.5f, -0.5f, -0.5f, 

        -0.5f,  0.5f, -0.5f, 
         0.5f,  0.5f, -0.5f, 
         0.5f,  0.5f,  0.5f, 
         0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f, -0.5f
  };

	Material triangleMat{ 1 };
	Geometry triangleGeo{ 1 };
	
  triangleGeo.setVertex(vertices, 36);
  triangleMat.setVertexShader(vertexShaderSource);
  triangleMat.setFragmentShader(fragmentShaderSource);

  Object *triangle = new Object();
  triangle->setGeometry(triangleGeo);
  triangle->setMaterial(triangleMat);
  objectsInScene_.push_back(triangle);

}

void App::Loop()
{

	while (!window_.ShouldClose())
	{
		input();
		update();
		draw();
	}

}

void App::End()
{
	window_.Terminate();
}

void App::input()
{
	window_.PollEvents();
	window_.GetMousePosition();
    camera_.input(&window_);
}

void App::update()
{
	camera_.update();
}

void App::ImGuiDraw() {

  if (ImGui::Begin("Test"))
  {

	  ImGui::Text("CAMERA POSITION:\n x = %f\n y = %f\n z = %f\n", camera_.cameraPos.x, camera_.cameraPos.y, camera_.cameraPos.z);
	  ImGui::Text("CAMERA FRONT:\n x = %f\n y = %f\n z = %f\n", camera_.cameraFront.x, camera_.cameraFront.y, camera_.cameraFront.z);
	  ImGui::Text("CAMERA UP:\n x = %f\n y = %f\n z = %f\n", camera_.cameraUp.x, camera_.cameraUp.y, camera_.cameraUp.z);
	  ImGui::Text("CAMERA RIGTH:\n x = %f\n y = %f\n z = %f\n", camera_.cameraRight.x, camera_.cameraRight.y, camera_.cameraRight.z);
	  ImGui::Text("YAW = %f\n PITCH = %f\n ROLL = %f\n", camera_.yaw, camera_.pitch, camera_.roll);


    ImGui::End();
  }

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void App::draw()
{

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ClearWindowCommand* cCommand = new ClearWindowCommand();
	cCommand->setColor(0.8f, 0.8f, 0.8f);
	commands_.push_back(cCommand);
	//window_.Clear();

	for each (Object * o in objectsInScene_)
	{
		o->draw(&commands_, &camera_);
	}

	for each (RenderCommand* com in commands_)
	{
		com->Action();
	}

  commands_.clear();

  ImGuiDraw();

	


	window_.SwapBuffers();
}


