
#include <clearwindow_rendercommand.h>
#include <GLEW/GL/glew.h>

using namespace VC;

ClearWindowCommand::~ClearWindowCommand()
{
}

ClearWindowCommand::ClearWindowCommand()
{
	color[0] = 0.8f;
	color[1] = 0.8f;
	color[2] = 0.8f;
}

void ClearWindowCommand::Action()
{
	glClearColor(color[0], color[1], color[2], 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CW);
	glDepthFunc(GL_LESS);
}

void ClearWindowCommand::setColor(float R, float G, float B)
{
	color[0] = R;
	color[1] = G;
	color[2] = B;
}
