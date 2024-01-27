
#include "stdafx.h"

#ifndef UNPACKBUFFER_H
#define	UNPACKBUFFER_H

class UnpackBuffer : public BufferObject
{
private:


public:
	__declspec(dllexport) 	  UnpackBuffer(GLuint count, GLintptr size, const void *data);
	__declspec(dllexport) ~UnpackBuffer();

	__declspec(dllexport) void update(GLintptr offset, GLintptr size, const void *data);
	__declspec(dllexport) void attach();
	__declspec(dllexport) void detach();
	__declspec(dllexport) void print() const;
};
#endif // !UNPACKBUFFER_H
#pragma once


