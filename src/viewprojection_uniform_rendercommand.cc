
#include <viewprojection_uniform_rendercommand.h>
#include <GLEW/GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace VC;

ViewProjectionUniformCommand::~ViewProjectionUniformCommand()
{

}

ViewProjectionUniformCommand::ViewProjectionUniformCommand()
{

}

void ViewProjectionUniformCommand::Action()
{
  u32 uniform_position = glGetUniformLocation(material_.getMaterialID(), "u_v_matrix");
  Vector3 aux = camera_->cameraPos + camera_->cameraFront;
  glm::mat4 view = glm::lookAt(glm::vec3(camera_->cameraPos.x, camera_->cameraPos.y, camera_->cameraPos.z),
      glm::vec3(aux.x, aux.y, aux.z),
      glm::vec3(camera_->cameraUp.x, camera_->cameraUp.y, camera_->cameraUp.z));
  float *mat = camera_->view.m;
  glUniformMatrix4fv(uniform_position, 1, GL_FALSE, (const GLfloat*)&view);

  uniform_position = glGetUniformLocation(material_.getMaterialID(), "u_p_matrix");
  glm::mat4 projection = glm::perspective(glm::radians(90.0f), 1280.0f / 720.0f, 0.1f, 1000.0f);
  mat = camera_->projection.m;
  glUniformMatrix4fv(uniform_position, 1, GL_FALSE, (const GLfloat*)&projection);

  uniform_position = glGetUniformLocation(material_.getMaterialID(), "u_m_matrix");
  Matrix4x4 model = Matrix4x4::Identity();
  glUniformMatrix4fv(uniform_position, 1, GL_FALSE, (const GLfloat*)model.m);

  
}

void ViewProjectionUniformCommand::setMaterial(Material mat)
{

#ifdef VERBOSE
  if (mat == nullptr)
  {
    printf("Material set in ViewProjectionUniformCommand is null\n");
  }
#endif

  material_ = mat;
}

void ViewProjectionUniformCommand::setCamera(Camera* cam)
{

#ifdef VERBOSE
  if (cam == nullptr)
  {
    printf("Camera set in ViewProjectionUniformCommand is null\n");
  }
#endif

  camera_ = cam;
}
