#include <material_rendercommand.h>
#include <GLEW/GL/glew.h>
#include <logger.h>

using namespace VC;


MaterialCommand::~MaterialCommand()
{

}

MaterialCommand::MaterialCommand()
{

}

void MaterialCommand::Action()
{
	if (material.getMaterialID() == 0)
	{
		const char* vertexShaderSource = material.getVertexShader();
		const char* fragmentShaderSource = material.getFragmentShader();
		
		u32 vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);
		if (!isShaderCompiled(vertexShader))
		{
			Logger::addMessage("[ERROR] : Vertex Shader did not compile");

		}
		else {
			Logger::addMessage("Vertex Shader compiled");
		}
		GLenum error = glGetError();
		if (error != 0) printf("[ERROR] :  vertex shader\n");
		u32 fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);
		if (!isShaderCompiled(fragmentShader))
		{
			
			Logger::addMessage("[ERROR] : Fragment Shader did not compile");

		}
		else {
			Logger::addMessage("Fragment Shader compiled");
			//printf("[BRO] : Fragment Shader compiled\n");
		}
		 error = glGetError();
		
		 if (error != 0)  Logger::addMessage("[ERROR] :  fragment shader");
		u32 shaderProgram;
		shaderProgram = glCreateProgram();
		material.setMaterialID(shaderProgram);
		glAttachShader(shaderProgram, vertexShader);
		 error = glGetError();
		if (error != 0) Logger::addMessage("[ERROR] :  attach vertex shader");
		glAttachShader(shaderProgram, fragmentShader);
		 error = glGetError();
		if (error != 0) Logger::addMessage("[ERROR] :  attach fragment shader");
		glLinkProgram(shaderProgram);
		 error = glGetError();
		if (error != 0) Logger::addMessage("[ERROR] :  link shader");
		
	}
	GLenum error = glGetError();
	if (error != 0) Logger::addMessage("[ERROR] :  material render command");
	glUseProgram(material.getMaterialID());

}

bool MaterialCommand::isShaderCompiled(u32 shaderID) {
  
  GLint param;

  glGetShaderiv(shaderID, GL_COMPILE_STATUS, &param);

  return param;
}

bool VC::MaterialCommand::isProgramLinked(u32 programID)
{
  GLint param;

  glGetProgramiv(programID, GL_LINK_STATUS, &param);
  GLenum error = glGetError();
  if (error != 0) Logger::addMessage("[ERROR] :  check link command");
  return param;
}

void MaterialCommand::setMaterial(u32 id)
{
	material = Material{ id };
}
