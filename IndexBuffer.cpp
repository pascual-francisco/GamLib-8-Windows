
#include "stdafx.h"

IndexBuffer::IndexBuffer(GLuint count, GLintptr size, const void *data)
{
	GLuint vertex = 0;
	void *zero = nullptr;
	bufferCount = count;
	bufferDataSize = GLuint(size);
	bufferTarget = GL_ELEMENT_ARRAY_BUFFER;

	glGenBuffers(1, &bufferObjectID);
	glBindBuffer(bufferTarget, bufferObjectID);

	if (data == nullptr)
	{
		GLuint vertex = 0;
		GLuint quad = 0;

		GLuint *tempData = new GLuint[bufferCount];
		for (uint i = 0; i < bufferCount; i++) { tempData[i] = 0; }

		for (uint i = 0; i < bufferCount; i++)
		{
			if (vertex == 0) { tempData[i] = (quad * 4); }
			if (vertex == 1) { tempData[i] = tempData[i - 1] + 1; }
			if (vertex == 2) { tempData[i] = tempData[i - 1] + 1; }
			if (vertex == 3) { tempData[i] = tempData[i - 1]; }
			if (vertex == 4) { tempData[i] = tempData[i - 1] + 1; }
			if (vertex == 5) { tempData[i] = tempData[i - 5]; }

			if (vertex < 5)
			{
				vertex++;
			}
			else
			{
				quad++;
				vertex = 0;
			}
		}

		glBufferData(bufferTarget, bufferCount * bufferDataSize, tempData, GL_DYNAMIC_DRAW);
		delete[] tempData;
	}
	else
	{
		glBufferData(bufferTarget, bufferCount * bufferDataSize, data, GL_DYNAMIC_DRAW);
	}
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &bufferObjectID);
}

void IndexBuffer::update(GLintptr offset, GLintptr size, const void *data)
{
	glBindBuffer(bufferTarget, bufferObjectID);
	glBufferSubData(bufferTarget, offset, size, data);
}

void IndexBuffer::attach()
{
	glBindBuffer(bufferTarget, bufferObjectID);
}

void IndexBuffer::detach()
{
	glBindBuffer(bufferTarget, 0);
}

void IndexBuffer::print() const
{
	cout << "*****************************************************" << endl;
	cout << "Index Buffer Info: " << endl;
	cout << "Buffer Object ID = " << bufferObjectID << endl;
	cout << "Buffer Target = GL_ELEMENT_ARRAY_BUFFER" << endl;
	cout << "Buffer Storage Format = GL_UNSIGNED_INT" << endl;
	cout << "Buffer Data Size = " << bufferDataSize << " Bytes" << endl;
	cout << "Buffer Count = " << bufferCount << " Indices" << endl;
	cout << "Buffer Size = " << bufferDataSize * bufferCount << " Bytes" << endl;
	cout << "*****************************************************" << endl;
}

/*
	zero = (void *)malloc(bufferCount * bufferDataSize);
	memset(zero, 0, bufferCount * bufferDataSize);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferCount * bufferDataSize, zero, GL_DYNAMIC_DRAW);
*/
