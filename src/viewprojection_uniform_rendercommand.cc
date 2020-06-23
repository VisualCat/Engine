
#include <viewprojection_uniform_rendercommand.h>
#include <GLEW/GL/glew.h>

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
  float *mat = camera_->view.m;
  glUniformMatrix4fv(uniform_position, 1, GL_FALSE, (const GLfloat*)mat);

  uniform_position = glGetUniformLocation(material_.getMaterialID(), "u_p_matrix");
  mat = camera_->projection.m;
  glUniformMatrix4fv(uniform_position, 1, GL_FALSE, (const GLfloat*)mat);

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
