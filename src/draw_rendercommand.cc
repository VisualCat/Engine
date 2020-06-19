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
	glDrawArrays(GL_TRIANGLES, 0, buffer_.getNumVertex());

}

void DrawCommand::setBuffer(u32 id)
{
	buffer_ = Buffer{ id };
}
