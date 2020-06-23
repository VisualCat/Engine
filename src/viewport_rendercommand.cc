
#include <viewport_rendercommand.h>
#include <GLEW/GL/glew.h>

using namespace VC;

ViewportCommand::~ViewportCommand()
{
}

ViewportCommand::ViewportCommand()
{
	x_ = 0;
	y_ = 0;
	width_ = 800;
	height_ = 600;
}

void ViewportCommand::Action()
{
	glViewport(x_, y_, width_, height_);
}

void ViewportCommand::setProperties(u32 width, u32 height, u32 x, u32 y)
{
	x_ = x;
	y_ = y;
	width_ = width;
	height_ = height;
}
