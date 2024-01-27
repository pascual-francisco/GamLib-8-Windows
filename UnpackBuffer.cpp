#include "stdafx.h"

UnpackBuffer::UnpackBuffer(GLuint count, GLintptr size, const void *data)
{
	bufferTarget = GL_PIXEL_UNPACK_BUFFER;
	bufferCount = count;
	bufferDataSize = size;

	glGenBuffers(1, &bufferObjectID);
	glBindBuffer(bufferTarget, bufferObjectID);
	glBufferData(bufferTarget, bufferCount * bufferDataSize, data, GL_DYNAMIC_COPY);
	glBindBuffer(bufferTarget, 0);


}

UnpackBuffer::~UnpackBuffer()
{

}

void UnpackBuffer::update(GLintptr offset, GLintptr size, const void *data)
{
	glBindBuffer(bufferTarget, bufferObjectID);
	glBufferSubData(bufferTarget, offset, size, data);
	glBindBuffer(bufferTarget, 0);
}

void UnpackBuffer::attach() 
{
	glBindBuffer(bufferTarget, bufferObjectID);
}

void UnpackBuffer::detach() 
{
	glBindBuffer(bufferTarget, 0);
}

void UnpackBuffer::print() const
{
	cout << "*****************************************************" << endl;
	cout << "Unpack Buffer Info:" << endl;
	BufferObject::print();
	cout << "*****************************************************" << endl;
}
