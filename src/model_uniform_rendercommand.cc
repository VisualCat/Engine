
#include <model_uniform_rendercommand.h>
#include <GLEW/GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace VC;

ModelUniformCommand::~ModelUniformCommand()
{

}

ModelUniformCommand::ModelUniformCommand()
{

}

void ModelUniformCommand::Action()
{
	
	u32 uniform_position = glGetUniformLocation(material_.getMaterialID(), "u_m_matrix");
	glm::mat4 model(
		glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	model = glm::translate(model, trans_.position);
	//model = glm::rotate(model,trans_.rotationFactor,trans_.rotation);
	model = glm::scale(model, trans_.scale);
	glUniformMatrix4fv(uniform_position, 1, GL_FALSE, (const GLfloat*)&model);
	GLenum error = glGetError();
	if (error != 0) printf("An error occurred, model render command\n");

}

void ModelUniformCommand::setMaterial(Material mat)
{

#ifdef VERBOSE
	if (mat == nullptr)
	{
		printf("Material set in ViewProjectionUniformCommand is null\n");
	}
#endif

	material_ = mat;
}

void ModelUniformCommand::setTransform(Transform trans)
{

#ifdef VERBOSE
	if (cam == nullptr)
	{
		printf("Camera set in ViewProjectionUniformCommand is null\n");
	}
#endif

	trans_ = trans;
}
