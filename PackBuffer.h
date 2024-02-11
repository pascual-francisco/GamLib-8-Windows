#pragma once
#include "stdafx.h"

namespace buffer
{
	#ifndef PACKBUFFER_H
	#define	PACKBUFFER_H

	class PackBuffer : public BufferObject
	{
	private:



	public:


		__declspec(dllexport) 	  PackBuffer(GLuint count, GLintptr size, const void* data);
		__declspec(dllexport) ~PackBuffer();

		__declspec(dllexport) void update(GLintptr offset, GLintptr size, const void* data);
		__declspec(dllexport) void attach();
		__declspec(dllexport) void detach();
		__declspec(dllexport) void print() const;
	};
	#endif // !PACKBUFFER_H
}


