
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

	GLuint bufferID;
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(float), vertices_.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


}

void BufferCommand::SetVertices(float* newVertices, u32 numOfVertices)
{
	for (u32 i = 0; i < numOfVertices*3; i++)
	{
		vertices_.push_back(newVertices[i]);
	}
}
