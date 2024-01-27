#pragma once
#include "stdafx.h"

#ifndef FRAMEBUFFER_H
#define	FRAMEBUFFER_H

class FrameBuffer : public BufferObject
{
	private:

	public:
		GLuint attachmentPoints[18];
		string frameBufferStatus;

		__declspec(dllexport) 	  FrameBuffer(GLuint target);
		__declspec(dllexport) ~FrameBuffer();


		__declspec(dllexport) void update(GLintptr offset, GLintptr size, const void *data);
		__declspec(dllexport) void attach();
		__declspec(dllexport) void attachRenderBuffer(RenderBuffer* buffer);
		__declspec(dllexport) void attachColor(GLuint point, GLuint buffer);
		__declspec(dllexport) void attachDepth(GLuint buffer);
		__declspec(dllexport) void attachStencil(GLuint buffer);
		__declspec(dllexport) void attachTexture(GLuint buffer);
		__declspec(dllexport) void attachDraw();
		__declspec(dllexport) void attachRead();
		__declspec(dllexport) void checkStatus();

		__declspec(dllexport) void detachPoints();
		__declspec(dllexport) void detach();
		__declspec(dllexport) void print() const;

};
#endif // !FRAMEBUFFER_H



