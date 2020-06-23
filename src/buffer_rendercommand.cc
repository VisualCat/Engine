
#include <buffer_rendercommand.h>
#include <GLEW/GL/glew.h>

using namespace VC;

BufferCommand::~BufferCommand()
{

}

BufferCommand::BufferCommand()
{

}

void BufferCommand::Action()
{
	if (geometry_.getGeometryID() == 0)
	{
		GLuint geometry_ID;
		glGenBuffers(1, &geometry_ID);
		geometry_.setGeometryID(geometry_ID);
		glBindBuffer(GL_ARRAY_BUFFER, geometry_.getGeometryID());
		glBufferData(GL_ARRAY_BUFFER, geometry_.getNumVertex() * sizeof(float), geometry_.getVertex(), GL_STATIC_DRAW);

	}
	glBindBuffer(GL_ARRAY_BUFFER, geometry_.getGeometryID());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


}

void BufferCommand::setGeometry(u32 id)
{
	geometry_ = Geometry{ id };
}
