
#include <app.h>

#include <GLEW/GL/glew.h>
#include <IMGUI/imgui_impl_glfw.h>
#include <IMGUI/imgui_impl_opengl3.h>

#include <constraints.h>

#include <logger.h>

#include <geometry.h>
#include <shader.h>
#include <material.h>
#include <clearwindow_rendercommand.h>
#include <transform_component.h>
#include <parent_component.h>
#include <render_component.h>
#include <render_system.h>

#include <glm/gtc/matrix_transform.hpp>

using namespace VC;

void App::Init()
{
	start_time = std::chrono::system_clock::now();
	Geometry::Inicialize(kMaxBuffers);
	Logger::addMessage("geometries initialized");
	Material::Inicialize(kMaxMaterials);
	Logger::addMessage("materials initialized");

	window_.Init();
	Logger::addMessage("window initialized");

	window_.CreateWindow(kWindowWidth, kWindowHeight, "Main Window");

	window_.MakeCurrentContext();
	camera_.init();
	Logger::addMessage("camera initialized");

	cordinator_.Init();
	Logger::addMessage("coordinator initialized");

	cordinator_.RegisterComponent<Transform>();
	cordinator_.RegisterComponent<Render>();
	cordinator_.RegisterComponent<Parent>();

	Logger::addMessage("components registered");


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

  transformsys_ = cordinator_.RegisterSystem<TransformSystem>();
  {
	  Signature signature;
	  signature.set(cordinator_.GetComponentType<Transform>());
	  signature.set(cordinator_.GetComponentType<Parent>());
	  cordinator_.SetSystemSignature<TransformSystem>(signature);
  }
  transformsys_->Init(&cordinator_);

  Logger::addMessage("systems registered");

	/*Shader vertexShader;
	Shader fragmentShader;
	vertexShader.LoadSource("path");
	fragmentShader.LoadSource("path");*/

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
	Geometry roadGeo{ 2 };
	
	if (!roadGeo.LoadOBJ("../bin/SM_Road_00.obj", false)) {
		Logger::addMessage("Did not load obj properly");
	}

	triangleGeo.CreatePrism();

  triangleMat.setVertexShader(vertexShaderSource);
  triangleMat.setFragmentShader(fragmentShaderSource);

  //Object *triangle = new Object();
  //triangle->setGeometry(triangleGeo);
  //triangle->setMaterial(triangleMat);
  //objectsInScene_.push_back(triangle);
  /*
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
  */
  Transform aux = {
			   glm::mat4(1.0f)
  };
  Render auxRender2 = {
	  triangleMat,
	  roadGeo
  };
	Render auxRender = {
		triangleMat,
		triangleGeo
	};

  //aux.transform = glm::rotate(aux.transform, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
  u32 entity = cordinator_.CreateEntity();
  cordinator_.AddComponent<Transform>(entity, aux);
  cordinator_.AddComponent<Render>(entity, auxRender2);
  entities_.push_back(entity);


  Transform aux1 = {
			 glm::mat4(1.0f)
  };
  aux1.transform = glm::translate(aux1.transform, glm::vec3(2.0f, 0.0f, 0.0f));
  aux1.transform = glm::scale(aux1.transform, glm::vec3(0.5f));
  u32 entity1 = cordinator_.CreateEntity();
  cordinator_.AddComponent<Transform>(entity1, aux1);
  cordinator_.AddComponent<Render>(entity1, auxRender);
  cordinator_.AddComponent<Parent>(entity1, Parent{entity,aux1});
  entities_.push_back(entity1);


  Transform aux2 = {
		   glm::mat4(1.0f)
  };
  aux2.transform = glm::translate(aux2.transform, glm::vec3(-2.0f, 0.0f, 0.0f));
  aux2.transform = glm::scale(aux2.transform, glm::vec3(2.0f));
  u32 entity2 = cordinator_.CreateEntity();
  cordinator_.AddComponent<Transform>(entity2, aux2);
  cordinator_.AddComponent<Render>(entity2, auxRender);
  cordinator_.AddComponent<Parent>(entity2, Parent{ entity, aux2});
  entities_.push_back(entity2);


  Transform aux3 = {
		   glm::mat4(1.0f)
  };
  aux3.transform = glm::translate(aux3.transform, glm::vec3(0.0f, 2.0f, 0.0f));
  aux3.transform = glm::scale(aux3.transform, glm::vec3(1.0f));
  u32 entity3 = cordinator_.CreateEntity();
  cordinator_.AddComponent<Transform>(entity3, aux3);
  cordinator_.AddComponent<Render>(entity3, auxRender);
  cordinator_.AddComponent<Parent>(entity3, Parent{ entity1, aux3 });
  entities_.push_back(entity3);

  Logger::addMessage("entities created");


  imguiHandler_.Init(&cordinator_);

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
  if (window_.getKeyPressed(Window::kVC_KEY_H))
  {
	  Transform& mov = cordinator_.GetComponent<Transform>(entities_[0]);
	  mov.transform = glm::translate(mov.transform,
			  glm::vec3(0.0f,0.0f,0.1f));
  }
}

void App::update()
{
	ClearWindowCommand* cCommand = new ClearWindowCommand();
	cCommand->setColor(0.8f, 0.8f, 0.8f);
	commands_.push_back(cCommand);

	camera_.update();
	float timer = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start_time).count()/1000.0f;

  //wavemovementsys_->Update(timer);
  //Logger::addMessage("wave movement system updated");
  transformsys_->Update();
  rendersys_->Update(&commands_, &camera_);
  //Logger::addMessage("render system updated");

  Logger::flush();
}

void App::ImGuiDraw() {

  if (ImGui::Begin("Test"))
  {

	  ImGui::Text("CAMERA POSITION:\n x = %f\n y = %f\n z = %f\n", camera_.cameraPos.x, camera_.cameraPos.y, camera_.cameraPos.z);
	  ImGui::Text("CAMERA FRONT:\n x = %f\n y = %f\n z = %f\n", camera_.cameraFront.x, camera_.cameraFront.y, camera_.cameraFront.z);
	  ImGui::Text("CAMERA UP:\n x = %f\n y = %f\n z = %f\n", camera_.cameraUp.x, camera_.cameraUp.y, camera_.cameraUp.z);
	  ImGui::Text("CAMERA RIGHT:\n x = %f\n y = %f\n z = %f\n", camera_.cameraRight.x, camera_.cameraRight.y, camera_.cameraRight.z);
	  ImGui::Text("YAW = %f\n PITCH = %f\n ROLL = %f\n", camera_.yaw, camera_.pitch, camera_.roll);


    ImGui::End();
  }

  imguiHandler_.HierarchyWindow(&entities_);
  imguiHandler_.InspectorWindow();

  bool demo = true;

  ImGui::ShowDemoWindow(&demo);

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void App::draw()
{

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	
	for each (RenderCommand* com in commands_)
	{
		com->Action();
    delete(com);
	}
	
  commands_.clear();

  ImGuiDraw();

	window_.SwapBuffers();
}


