
#include <GLEW/GL/glew.h>
#include <draw_rendercommand.h>

using namespace VC;

DrawCommand::~DrawCommand()
{

}

DrawCommand::DrawCommand()
{

}

void DrawCommand::Action()
{

  unsigned int posSize = geometry_.getVertexSizeInBytes();
  unsigned int normSize = geometry_.getNormalsSizeInBytes();
  unsigned int uvSize = geometry_.getUVsSizeInBytes();

  GLint numOfActiveAttributes = 0;
  glGetProgramiv(material_.getMaterialID(), GL_ACTIVE_ATTRIBUTES, &numOfActiveAttributes);

  unsigned int whereToBindAtttribute = 0;
  unsigned int myOffset = 0;

  glBindBuffer(GL_ARRAY_BUFFER, geometry_.getVerticesBufferID());

  for (u32 i = 0; i < numOfActiveAttributes; i++)
  {
    whereToBindAtttribute = i;
    switch (i) {

    case 0://POSITIONS
      glVertexAttribPointer(whereToBindAtttribute, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)myOffset);
      glEnableVertexAttribArray(whereToBindAtttribute);
      break;
    case 1://NORMALS
      myOffset = posSize;
      glVertexAttribPointer(whereToBindAtttribute, 3, GL_FLOAT, GL_TRUE, 0, (GLvoid*)myOffset);
      glEnableVertexAttribArray(whereToBindAtttribute);
      break;
    case 2://UVS
      myOffset = posSize + normSize;
      glVertexAttribPointer(whereToBindAtttribute, 2, GL_FLOAT, GL_TRUE, 0, (GLvoid*)myOffset);
      glEnableVertexAttribArray(whereToBindAtttribute);
      break;
    case 3:
      break;

    }
  }

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry_.getElementsBufferID());
	glDrawElements(GL_TRIANGLES, geometry_.getNumElements(), GL_UNSIGNED_INT, geometry_.getElements());
  GLenum error = glGetError();
  if (error != 0) printf("An error occurred\n");
}

void DrawCommand::setGeometry(u32 id)
{
  geometry_ = Geometry{ id };
}

void DrawCommand::setMaterial(u32 id)
{
  material_ = Material{ id };
}

