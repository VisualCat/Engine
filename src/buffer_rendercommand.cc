
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
	if (buffer_.getBufferID() == 0)
	{
		GLuint bufferID;
		glGenBuffers(1, &bufferID);
		buffer_.setBufferID(bufferID);
		glBindBuffer(GL_ARRAY_BUFFER, buffer_.getBufferID());
		glBufferData(GL_ARRAY_BUFFER, buffer_.getNumVertex() * sizeof(float), buffer_.getVertex(), GL_STATIC_DRAW);

	}
	glBindBuffer(GL_ARRAY_BUFFER, buffer_.getBufferID());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


}

void BufferCommand::setBuffer(u32 id)
{
	buffer_ = Buffer{ id };
}
