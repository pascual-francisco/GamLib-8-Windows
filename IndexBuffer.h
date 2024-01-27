
#include "stdafx.h"

#ifndef INDEXBUFFER_H
#define	INDEXBUFFER_H

class IndexBuffer: public BufferObject
{
	public:
		__declspec(dllexport) 	  IndexBuffer(GLuint count, GLintptr size, const void *data);
		__declspec(dllexport) ~IndexBuffer();

		__declspec(dllexport) void update(GLintptr offset, GLintptr size, const void *data);
		__declspec(dllexport) void attach() ;
		__declspec(dllexport) void detach() ;
		__declspec(dllexport) void print() const;
};
#endif // !INDEXBUFFER_H
#pragma once
