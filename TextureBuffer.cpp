#include "stdafx.h"

TextureBuffer::TextureBuffer(GLuint count, GLintptr size, const void *data, GLuint format, GLuint unit)
{	
	textureUnit = unit;
	bufferCount = count;
	bufferDataSize = size;
	bufferStorageFormat = format;
	bufferTarget = GL_TEXTURE_BUFFER;
	
	glGenBuffers(1, &bufferObjectID);
	glBindBuffer(GL_TEXTURE_BUFFER, bufferObjectID);
	glBufferData(GL_TEXTURE_BUFFER, bufferCount * bufferDataSize, data, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_TEXTURE_BUFFER, 0);
}

TextureBuffer::~TextureBuffer()
{
	
}

void TextureBuffer::update(GLintptr offset, GLintptr size, const void *data)
{
	glBufferSubData(GL_TEXTURE_BUFFER, offset, size, data);
}

void TextureBuffer::attach() 
{
	glActiveTexture(textureUnit);
	glBindBuffer(GL_TEXTURE_BUFFER, bufferObjectID);
	glTexBuffer(GL_TEXTURE_BUFFER, bufferStorageFormat, bufferObjectID);
}

void TextureBuffer::detach() 
{
	glBindBuffer(GL_TEXTURE_BUFFER, 0);
}

void TextureBuffer::print() const
{
	cout << "*****************************************************" << endl;
	cout << "Texture Buffer Info:" << endl;
	BufferObject::print();
	cout << "*****************************************************" << endl;
}
