
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
#include <transform_component.h>
#include <render_component.h>
#include <render_system.h>

using namespace VC;

void App::Init()
{
	start_time = std::chrono::system_clock::now();
	Geometry::Inicialize(kmaxBuffers);
	Material::Inicialize(kmaxMaterials);

	window_.Init();
	window_.CreateWindow(kWindowWidth, kWindowHeight, "Main Window");

	window_.MakeCurrentContext();
	camera_.init();

	cordinator_.Init();
	cordinator_.RegisterComponent<Transform>();
	cordinator_.RegisterComponent<Render>();

	rendersys_ = cordinator_.RegisterSystem<RenderSystem>();
	{
		Signature signature;
		signature.set(cordinator_.GetComponentType<Render>());
		signature.set(cordinator_.GetComponentType<Transform>());
		cordinator_.SetSystemSignature<RenderSystem>(signature);
	}
	rendersys_->Init(&cordinator_);

  wavemovementsys_ = cordinator_.RegisterSystem<WaveMovementSystem>();
  {
    Signature signature;
    signature.set(cordinator_.GetComponentType<Transform>());
    cordinator_.SetSystemSignature<WaveMovementSystem>(signature);
  }
  wavemovementsys_->Init(&cordinator_);

	const char* vertexShaderSource = R"(
		#version 330 core

		layout (location = 0) in vec3 aPos;
		layout (location = 1) in vec3 aNormal;

    uniform mat4 u_v_matrix;
    uniform mat4 u_p_matrix;
    uniform mat4 u_m_matrix;

    out vec3 normal;

    void main()
		{
        
       normal = aNormal * 0.5 + 0.5;

           
       mat4 mvp = u_p_matrix * u_v_matrix * u_m_matrix;
		   gl_Position = mvp * vec4(aPos.x, aPos.y, aPos.z, 1.0);
		}
	)";

	const char* fragmentShaderSource = R"(
		#version 330 core
		out vec4 FragColor;
    
    in vec3 normal;

		void main()
		{
			FragColor = vec4(normal, 1.0f);
		} 
	)";



	Material triangleMat{ 1 };
	Geometry triangleGeo{ 1 };
	
  triangleGeo.CreatePrism();

  triangleMat.setVertexShader(vertexShaderSource);
  triangleMat.setFragmentShader(fragmentShaderSource);

  //Object *triangle = new Object();
  //triangle->setGeometry(triangleGeo);
  //triangle->setMaterial(triangleMat);
  //objectsInScene_.push_back(triangle);

  for (s32 i = -5; i < 5; i++)
  {
	  for (s32 j = -5; j < 5; j++)
	  {
		  Transform aux = {
			   glm::vec3(i*2,j*2,0.0f),
			   glm::vec3(0.0f),
			   0.0f,
			   glm::vec3(1.0f)
		  };
		  Render auxRender = {
			  triangleMat,
			  triangleGeo
		  };
		  u32 entity = cordinator_.CreateEntity();
		  cordinator_.AddComponent<Transform>(entity, aux);
		  cordinator_.AddComponent<Render>(entity, auxRender);
		  entities_.push_back(entity);
	  }
  }
	 

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
	ClearWindowCommand* cCommand = new ClearWindowCommand();
	cCommand->setColor(0.8f, 0.8f, 0.8f);
	commands_.push_back(cCommand);

	camera_.update();
	float timer = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start_time).count()/1000.0f;

  //wavemovementsys_->Update(timer);
  //rendersys_->Update(&commands_, &camera_);
  
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

	//window_.Clear();

	//for each (Object * o in objectsInScene_)
	//{
	//	o->draw(&commands_, &camera_);
	//}
	
	for each (RenderCommand* com in commands_)
	{
		com->Action();
	}
	//commands_.erase(commands_.begin(), commands_.end());
  commands_.clear();

  ImGuiDraw();

	window_.SwapBuffers();
}


