#include "stdafx.h"

PixelBuffer::PixelBuffer(GLuint count, GLintptr size, const void *data, GLenum target)
{
	bufferCount = count;
	bufferDataSize = size;
	bufferTarget = target;

	glGenBuffers(1, &bufferObjectID);
	glBindBuffer(bufferTarget, bufferObjectID);

	if(target == GL_PIXEL_UNPACK_BUFFER || target == GL_PIXEL_PACK_BUFFER)
	{
		bufferTarget = target;
	}
	else
	{
		bufferTarget = GL_PIXEL_PACK_BUFFER;
	}	

	glBufferData(bufferTarget, bufferCount * bufferDataSize, data, GL_DYNAMIC_COPY);
	glBindBuffer(bufferTarget, 0);
}


PixelBuffer::~PixelBuffer()
{

}

void PixelBuffer::update(GLintptr offset, GLintptr size, const void *data)
{
	glBindBuffer(bufferTarget, bufferObjectID);
	glBufferSubData(bufferTarget, offset, size, data);
	glBindBuffer(bufferTarget, 0);
}

void PixelBuffer::attach() 
{
	glBindBuffer(bufferTarget, bufferObjectID);
}

void PixelBuffer::detach() 
{
	glBindBuffer(bufferTarget, 0);
}

void PixelBuffer::print() const
{
	cout << "*****************************************************" << endl;
	cout << "Pixel Buffer Info:" << endl;
	BufferObject::print();
	cout << "*****************************************************" << endl;
}

void PixelBuffer::attachPack()
{
	bufferTarget = GL_PIXEL_PACK_BUFFER;
	glBindBuffer(bufferTarget, bufferObjectID);
}

void PixelBuffer::attachUnpack()
{
	bufferTarget = GL_PIXEL_UNPACK_BUFFER;
	glBindBuffer(bufferTarget, bufferObjectID);
}
