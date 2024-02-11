
#include "stdafx.h"

namespace buffer
{

	VertexBuffer::VertexBuffer(GLuint count, GLintptr size, const void* data)
	{
		bufferCount = count;
		bufferDataSize = size;

		glGenBuffers(1, &bufferObjectID);
		glBindBuffer(GL_ARRAY_BUFFER, bufferObjectID);
		glBufferData(GL_ARRAY_BUFFER, bufferCount * bufferDataSize, data, GL_DYNAMIC_DRAW);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &bufferObjectID);
	}

	void VertexBuffer::update(GLintptr offset, GLintptr size, const void* data)
	{
		glBindBuffer(GL_ARRAY_BUFFER, bufferObjectID);
		glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
	}

	void VertexBuffer::attach()
	{
		glBindBuffer(GL_ARRAY_BUFFER, bufferObjectID);
	}

	void VertexBuffer::detach()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexBuffer::print() const
	{
		cout << "*****************************************************" << endl;
		cout << "Vertex Buffer Info:" << endl;
		BufferObject::print();
		cout << "*****************************************************" << endl;
	}
}