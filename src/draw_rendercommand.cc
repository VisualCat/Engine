
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
	glDrawArrays(GL_TRIANGLES, 0, geometry_.getNumVertex());

}

void DrawCommand::setGeometry(u32 id)
{
  geometry_ = Geometry{ id };
}
