
#include <buffer_rendercommand.h>
#include <GLEW/GL/glew.h>
#include <logger.h>

using namespace VC;

BufferCommand::~BufferCommand()
{

}

BufferCommand::BufferCommand()
{

}

void BufferCommand::Action()
{

  
  unsigned int posSize = geometry_.getVertexSizeInBytes();
  unsigned int normSize = geometry_.getNormalsSizeInBytes();
  unsigned int uvSize = geometry_.getUVsSizeInBytes();

	if (geometry_.getVerticesBufferID() == 0)
	{
		GLuint geometry_ID;
		glGenBuffers(1, &geometry_ID);
		geometry_.setVerticesBufferID(geometry_ID);
		glBindBuffer(GL_ARRAY_BUFFER, geometry_.getVerticesBufferID());
    
        unsigned int totalSize = posSize + normSize + uvSize;
        glBufferData(GL_ARRAY_BUFFER, totalSize, nullptr, GL_STATIC_DRAW);

   

        unsigned int myOffset = 0;
        glBufferSubData(GL_ARRAY_BUFFER, myOffset, posSize, geometry_.getVertex());
        myOffset += posSize;
        glBufferSubData(GL_ARRAY_BUFFER, myOffset, normSize, geometry_.getNormals());
        myOffset += normSize;
        //glBufferSubData(GL_ARRAY_BUFFER, myOffset, uvSize, geometry_.getUVs());
        //myOffset += uvSize;

        GLuint elements_ID;
        glGenBuffers(1, &elements_ID);
        geometry_.setElementsBufferID(elements_ID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry_.getElementsBufferID());
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, geometry_.getNumElements() * sizeof(unsigned int), geometry_.getElements(), GL_STATIC_DRAW);
        Logger::addMessage("Buffer created");
		GLenum error = glGetError();
		if (error != 0) Logger::addMessage("[ERROR] : buffer render command");
    }


}

void BufferCommand::setGeometry(u32 id)
{
	geometry_ = Geometry{ id };
}


