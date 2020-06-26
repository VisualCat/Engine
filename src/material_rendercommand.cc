#include <material_rendercommand.h>
#include <GLEW/GL/glew.h>

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
      printf("[ERROR] : Vertex Shader did not compile\n");
    }
    else {
      printf("[BRO] : Vertex Shader compiled\n");
    }

    u32 fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);
    if (!isShaderCompiled(fragmentShader))
    {
      printf("[ERROR] : Fragment Shader did not compile\n");
    }
    else {
      printf("[BRO] : Fragment Shader compiled\n");
    }

    u32 shaderProgram;
		shaderProgram = glCreateProgram();
		material.setMaterialID(shaderProgram);
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
    if (!isProgramLinked(fragmentShader))
    {
      printf("[ERROR] : Program did not link\n");
    }
    else {
      printf("[BRO] : Program linked\n");
    }
	}
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

  return param;
}

void MaterialCommand::setMaterial(u32 id)
{
	material = Material{ id };
}
