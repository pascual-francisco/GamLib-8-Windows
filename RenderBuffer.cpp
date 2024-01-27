#include "stdafx.h"

RenderBuffer::RenderBuffer(GLenum  target, GLenum  attachPoint, GLuint format, GLsizei w, GLsizei h)
{
	bufferTarget = target;
	attachment = attachPoint;
	bufferStorageFormat = format;
	width = w;
	height = h;

	glGenRenderbuffers(1, &bufferObjectID);
	glBindRenderbuffer(GL_RENDERBUFFER, bufferObjectID);	
	glRenderbufferStorage(GL_RENDERBUFFER, bufferStorageFormat, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);	
}

RenderBuffer::~RenderBuffer()
{
	glDeleteRenderbuffers(1, &bufferObjectID);
}


void RenderBuffer::update(GLintptr offset, GLintptr size, const void *data)
{
}

void RenderBuffer::attach() 
{
	glBindRenderbuffer(GL_RENDERBUFFER, bufferObjectID);	
}

void RenderBuffer::detach() 
{
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void RenderBuffer::print() const
{
	cout << "*****************************************************" << endl;
	cout << "Render Buffer Info:" << endl;
	BufferObject::print();
	cout << "Image Size = " << width << " x "<<height << endl;	
	
	cout << "Buffer Attachment = ";
	
	if (attachment == GL_COLOR_ATTACHMENT0)
		cout << "GL_COLOR_ATTACHMENT0" << endl;

	if (attachment == GL_COLOR_ATTACHMENT1)
		cout << "GL_COLOR_ATTACHMENT1" << endl;

	if (attachment == GL_COLOR_ATTACHMENT2)
		cout << "GL_COLOR_ATTACHMENT2" << endl;

	if (attachment == GL_COLOR_ATTACHMENT3)
		cout << "GL_COLOR_ATTACHMENT3" << endl;

	if (attachment == GL_COLOR_ATTACHMENT4)
		cout << "GL_COLOR_ATTACHMENT4" << endl;

	if (attachment == GL_COLOR_ATTACHMENT5)
		cout << "GL_COLOR_ATTACHMENT5" << endl;

	if (attachment == GL_COLOR_ATTACHMENT6)
		cout << "GL_COLOR_ATTACHMENT6" << endl;

	if (attachment == GL_COLOR_ATTACHMENT7)
		cout << "GL_COLOR_ATTACHMENT7" << endl;

	if (attachment == GL_DEPTH_ATTACHMENT)
		cout << "GL_DEPTH_ATTACHMENT" << endl;
	
	if (attachment == GL_STENCIL_ATTACHMENT)
		cout << "GL_STENCIL_ATTACHMENT" << endl;

	if (attachment == GL_DEPTH_STENCIL_ATTACHMENT)
		cout << "GL_DEPTH_STENCIL_ATTACHMENT" << endl;

	cout << "*****************************************************" << endl;
}
