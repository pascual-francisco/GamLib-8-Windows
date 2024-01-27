#include "stdafx.h"

#ifndef RENDERBUFFER_H
#define	RENDERBUFFER_H

class RenderBuffer : public BufferObject
{
	private:

	public:
	GLenum	attachment;
	GLsizei	width;
	GLsizei	height;

	__declspec(dllexport) RenderBuffer(GLenum  target, GLenum attachPoint, GLuint format, GLsizei w, GLsizei h);
	__declspec(dllexport) ~RenderBuffer();
	__declspec(dllexport) void update(GLintptr offset, GLintptr size, const void *data);
	__declspec(dllexport) void attach();
	__declspec(dllexport) void detach();
	__declspec(dllexport) void print() const;
};
#endif // !RENDERBUFFER_H


