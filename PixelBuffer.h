
#include "stdafx.h"

#ifndef PIXELBUFFER_H
#define	PIXELBUFFER_H

class PixelBuffer : public BufferObject
{
private:


	public:
		__declspec(dllexport) 	  PixelBuffer(GLuint count, GLintptr size, const void *data, GLenum target);
		__declspec(dllexport) ~PixelBuffer();

		__declspec(dllexport) 	   void update(GLintptr offset, GLintptr size, const void *data);
		__declspec(dllexport) void attach() ;
		__declspec(dllexport) void detach() ;
		__declspec(dllexport) void print() const;

		__declspec(dllexport) void attachPack();
		__declspec(dllexport) void attachUnpack();

};
#endif // !PIXELBUFFER_H



