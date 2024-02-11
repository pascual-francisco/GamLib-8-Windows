#include "stdafx.h"

namespace buffer
{
	#ifndef TEXTUREBUFFER_H
	#define	TEXTUREBUFFER_H

	class TextureBuffer : public BufferObject
	{	
		public:
		GLuint textureUnit;

		__declspec(dllexport) TextureBuffer(GLuint count, GLintptr size, const void* data, GLuint format, GLuint unit);
		__declspec(dllexport) ~TextureBuffer();
		
		__declspec(dllexport) void init(GLuint count, GLintptr size, const void* data, GLuint format, GLuint unit);
		__declspec(dllexport) void update(GLintptr offset, GLintptr size, const void* data);
		__declspec(dllexport) void attach();
		__declspec(dllexport) void detach();
		__declspec(dllexport) void print() const;

	};
	#endif // !TEXTUREBUFFER_H
}


