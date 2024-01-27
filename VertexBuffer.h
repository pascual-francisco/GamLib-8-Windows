
#include "stdafx.h"

#ifndef VERTEXBUFFER_H
#define	VERTEXBUFFER_H

class VertexBuffer: public BufferObject
{
	private:


	public:
		__declspec(dllexport) VertexBuffer(GLuint count, GLintptr size, const void *data);
		__declspec(dllexport) ~VertexBuffer();


		__declspec(dllexport) void update(GLintptr offset, GLintptr size, const void *data);
		__declspec(dllexport) void attach();
		__declspec(dllexport) void detach();
		__declspec(dllexport) void print() const;
};
#endif // !VERTEXBUFFER_H


