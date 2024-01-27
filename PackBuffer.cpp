#include "PackBuffer.h"

PackBuffer::PackBuffer(GLuint count, GLintptr size, const void *data)
{
	bufferCount = count;
	bufferDataSize = size;
	bufferTarget = GL_PIXEL_PACK_BUFFER;	

	glGenBuffers(1, &bufferObjectID);
	glBindBuffer(bufferTarget, bufferObjectID);
	glBufferData(bufferTarget, bufferCount * bufferDataSize, data, GL_DYNAMIC_COPY);
	glBindBuffer(bufferTarget, 0);
}

PackBuffer::~PackBuffer()
{

}

void PackBuffer::update(GLintptr offset, GLintptr size, const void *data)
{
	glBindBuffer(bufferTarget, bufferObjectID);
	glBufferSubData(bufferTarget, offset, size, data);
	glBindBuffer(bufferTarget, 0);
}

void PackBuffer::attach() 
{
	glBindBuffer(bufferTarget, bufferObjectID);
}

void PackBuffer::detach() 
{
	glBindBuffer(bufferTarget, 0);
}

void PackBuffer::print() const
{
	cout << "*****************************************************" << endl;
	cout << "Pack Buffer Info:" << endl;
	BufferObject::print();	
	cout << "*****************************************************" << endl;
}
