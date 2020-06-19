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
		
		unsigned int vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);



		unsigned int fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		unsigned int shaderProgram;
		shaderProgram = glCreateProgram();
		material.setMaterialID(shaderProgram);
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

	}
	glUseProgram(material.getMaterialID());

}

void MaterialCommand::setMaterial(u32 id)
{
	material = Material{ id };
}
