
#include "stdafx.h"

#ifndef BUFFEROBJECT_H
#define	BUFFEROBJECT_H

class BufferObject
{
	public:
	GLuint		bufferTarget;
	GLuint		bufferObjectID;
	GLuint		bufferDataSize;
	GLuint		bufferCount;
	GLuint		bufferStorageFormat;

	  BufferObject()
	{
		bufferTarget = 0;
		bufferObjectID = 0;
		bufferDataSize = 0;
		bufferCount = 0;
		bufferStorageFormat = 0;
	};
	  __declspec(dllexport) 	  BufferObject(GLuint count, GLintptr size, const void *data) {};
	  __declspec(dllexport) ~BufferObject() {};

	  __declspec(dllexport) virtual void update(GLintptr offset, GLintptr size, const void *data) = 0 ;
	  __declspec(dllexport) virtual void attach() = 0;
	  __declspec(dllexport) virtual void detach() = 0 ;
	  __declspec(dllexport) virtual void print() const
	{
		cout << "Buffer Object ID = " << bufferObjectID << endl;

		cout << "Buffer Target = ";

		if (bufferTarget == GL_DRAW_FRAMEBUFFER)
			cout << "GL_DRAW_FRAMEBUFFER" << endl;

		if (bufferTarget == GL_READ_FRAMEBUFFER)
			cout << "GL_READ_FRAMEBUFFER" << endl;

		if (bufferTarget == GL_RENDERBUFFER)
			cout << "GL_RENDERBUFFER" << endl;

		if (bufferTarget == GL_PIXEL_PACK_BUFFER)
			cout << "GL_PIXEL_PACK_BUFFER" << endl;

		if (bufferTarget == GL_PIXEL_UNPACK_BUFFER)
			cout << "GL_PIXEL_UNPACK_BUFFER" << endl;

		if (bufferTarget == GL_TEXTURE_BUFFER)
			cout << "GL_TEXTURE_BUFFER" << endl;

		if (bufferTarget == GL_ARRAY_BUFFER)
			cout << "GL_ARRAY_BUFFER" << endl;

		if (bufferTarget == GL_ELEMENT_ARRAY_BUFFER)
			cout << "GL_ELEMENT_ARRAY_BUFFER" << endl;

		cout << "Buffer Storage Format = ";

		if (bufferStorageFormat == 0)
			cout << "NONE" << endl;

		if (bufferStorageFormat == GL_RGBA8)
			cout << "GL_RGBA8" << endl;

		if (bufferStorageFormat == GL_RGBA)
			cout << "GL_RGBA" << endl;

		if (bufferStorageFormat == GL_RGB)
			cout << "GL_RGB" << endl;


		if (bufferStorageFormat == GL_DEPTH_COMPONENT)
			cout << "GL_DEPTH_COMPONENT" << endl;

		if (bufferStorageFormat == GL_DEPTH_COMPONENT16)
			cout << "GL_DEPTH_COMPONENT16" << endl;

		if (bufferStorageFormat == GL_DEPTH_COMPONENT24)
			cout << "GL_DEPTH_COMPONENT24" << endl;

		if (bufferStorageFormat == GL_DEPTH_COMPONENT32)
			cout << "GL_DEPTH_COMPONENT32" << endl;

		if (bufferStorageFormat == GL_DEPTH24_STENCIL8)
			cout << "GL_DEPTH24_STENCIL8" << endl;

		if (bufferStorageFormat == GL_DEPTH32F_STENCIL8)
			cout << "GL_DEPTH24_STENCIL8" << endl;

		if (bufferStorageFormat == GL_DEPTH32F_STENCIL8)
			cout << "GL_DEPTH24_STENCIL8" << endl;

		if (bufferStorageFormat == GL_DEPTH_STENCIL)
			cout << "GL_DEPTH_STENCIL" << endl;

		if (bufferStorageFormat == GL_STENCIL_INDEX8)
			cout << "GL_STENCIL_INDEX8" << endl;

		cout << "Buffer Data Size = " << bufferDataSize <<" Bytes"<< endl;

		cout << "Buffer Count = " << bufferCount <<" Pixels"<< endl;

		cout << "Buffer Size = " << bufferDataSize * bufferCount << " Bytes" << endl;

	};
};
#endif // !BUFFEROBJECT_H
#pragma once
