#include "stdafx.h"

FrameBuffer::FrameBuffer(GLuint target)
{
	for (uint i = 0; i < 18; i++)
		attachmentPoints[i] = 0;

	frameBufferStatus = " ";
	bufferTarget = target;
	glGenFramebuffers(1, &bufferObjectID);		
	glBindFramebuffer(bufferTarget, bufferObjectID);
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &bufferObjectID);
}

void FrameBuffer::update(GLintptr offset, GLintptr size, const void *data){}

void FrameBuffer::checkStatus()
{
	GLenum fboStatus = glCheckFramebufferStatus(bufferTarget);
	if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
	{
		switch (fboStatus)
		{
			case GL_FRAMEBUFFER_UNDEFINED:
				// Oops, no window exists?
				frameBufferStatus = "GL_FRAMEBUFFER_UNDEFINED";
				break;

			case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
				// Check the status of each attachment
				frameBufferStatus = "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT";
				break;

			case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
				// Attach at least one buffer to the FBO
				frameBufferStatus = "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT";
				break;

			case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
				// Check that all attachments enabled via
				// glDrawBuffers exist in FBO
				frameBufferStatus = "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER";
				break;

			case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
				// Check that the buffer specified via
				// glReadBuffer exists in FBO
				frameBufferStatus = "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER";
				break;

			case GL_FRAMEBUFFER_UNSUPPORTED:
				// Reconsider formats used for attached buffers
				frameBufferStatus = "GL_FRAMEBUFFER_UNSUPPORTED";
				break;

			case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
				// Make sure the number of samples for each
				// attachment is the same
				frameBufferStatus = "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE";
				break;

			case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
				// Make sure the number of layers for each
				// attachment is the same
				frameBufferStatus = "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS";
				break;

			default:
			break;
		}
	}
	else
	{
		frameBufferStatus = "GL_FRAMEBUFFER_COMPLETE";
	}
}

void FrameBuffer::attach()
{
	glBindFramebuffer(bufferTarget, bufferObjectID);	
	
}

void FrameBuffer::attachRenderBuffer(RenderBuffer *buffer)
{
	if (buffer->attachment == GL_COLOR_ATTACHMENT0)							  
		attachColor(0, buffer->bufferObjectID);
	
	if (buffer->attachment == GL_COLOR_ATTACHMENT1)
		attachColor(1, buffer->bufferObjectID);

	if (buffer->attachment == GL_COLOR_ATTACHMENT2)
		attachColor(2, buffer->bufferObjectID);

	if (buffer->attachment == GL_COLOR_ATTACHMENT3)
		attachColor(3, buffer->bufferObjectID);

	if (buffer->attachment == GL_COLOR_ATTACHMENT4)
		attachColor(4, buffer->bufferObjectID);

	if (buffer->attachment == GL_COLOR_ATTACHMENT5)
		attachColor(5, buffer->bufferObjectID);

	if (buffer->attachment == GL_COLOR_ATTACHMENT6)
		attachColor(6, buffer->bufferObjectID);

	if (buffer->attachment == GL_COLOR_ATTACHMENT7)
		attachColor(7, buffer->bufferObjectID);

	if (buffer->attachment == GL_DEPTH_ATTACHMENT)
		attachDepth(buffer->bufferObjectID);

	if (buffer->attachment == GL_STENCIL_ATTACHMENT)
		attachStencil(buffer->bufferObjectID);

	if (buffer->attachment == GL_DEPTH_STENCIL_ATTACHMENT)
	{
		attachmentPoints[16] = buffer->bufferObjectID;
		attachmentPoints[17] = buffer->bufferObjectID;
		
		glBindFramebuffer(bufferTarget, bufferObjectID);
		glFramebufferRenderbuffer(bufferTarget, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, buffer->bufferObjectID);
	}
		
}

void FrameBuffer::attachTexture(GLuint buffer)
{
	glBindFramebuffer(bufferTarget, bufferObjectID);

}

void FrameBuffer::attachColor(GLuint point, GLuint buffer)
{
	if (point <= 7)
	{
		attachmentPoints[point] = buffer;
		glBindFramebuffer(bufferTarget, bufferObjectID);
		glFramebufferRenderbuffer(bufferTarget, GL_COLOR_ATTACHMENT0 + point, GL_RENDERBUFFER, buffer);		
	}
}

void FrameBuffer::attachDepth(GLuint buffer)
{
	attachmentPoints[16] = buffer;
	glBindFramebuffer(bufferTarget, bufferObjectID);
	glFramebufferRenderbuffer(bufferTarget, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, buffer);
}

void FrameBuffer::attachStencil(GLuint buffer)
{
	attachmentPoints[17] = buffer;
	glBindFramebuffer(bufferTarget, bufferObjectID);
	glFramebufferRenderbuffer(bufferTarget, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, buffer);
}

void FrameBuffer::attachDraw()
{
	bufferTarget = GL_DRAW_FRAMEBUFFER;
	glBindFramebuffer(bufferTarget, bufferObjectID);
}

void FrameBuffer::attachRead()
{
	bufferTarget = GL_READ_FRAMEBUFFER;
	glBindFramebuffer(bufferTarget, bufferObjectID);
}

void FrameBuffer::detachPoints()
{
	for (uint i = 0; i < 18; i++)
	{
		attachmentPoints[i] = 0;
		glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_RENDERBUFFER, 0);
	}
	glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, 0);
}

void FrameBuffer::detach()
{
	glBindFramebuffer(bufferTarget, 0);
	
}

void FrameBuffer::print() const
{
	cout << "*****************************************************" << endl;
	cout << "Frame Buffer Info:" << endl;
	BufferObject::print();

	cout <<"Frame Buffer Status = "<< frameBufferStatus << endl;
	cout << "Buffer ID on Color Attachment 00 = " << attachmentPoints[0] << endl;
	cout << "Buffer ID on Color Attachment 01 = " << attachmentPoints[1] << endl;
	cout << "Buffer ID on Color Attachment 02 = " << attachmentPoints[2] << endl;
	cout << "Buffer ID on Color Attachment 03 = " << attachmentPoints[3] << endl;
	cout << "Buffer ID on Color Attachment 04 = " << attachmentPoints[4] << endl;
	cout << "Buffer ID on Color Attachment 05 = " << attachmentPoints[5] << endl;
	cout << "Buffer ID on Color Attachment 06 = " << attachmentPoints[6] << endl;
	cout << "Buffer ID on Color Attachment 07 = " << attachmentPoints[7] << endl;
	cout << "Buffer ID on Color Attachment 08 = " << attachmentPoints[8] << endl;
	cout << "Buffer ID on Color Attachment 09 = " << attachmentPoints[9] << endl;
	cout << "Buffer ID on Color Attachment 10 = " << attachmentPoints[10] << endl;
	cout << "Buffer ID on Color Attachment 11 = " << attachmentPoints[11] << endl;
	cout << "Buffer ID on Color Attachment 12 = " << attachmentPoints[12] << endl;
	cout << "Buffer ID on Color Attachment 13 = " << attachmentPoints[13] << endl;
	cout << "Buffer ID on Color Attachment 14 = " << attachmentPoints[14] << endl;
	cout << "Buffer ID on Color Attachment 15 = " << attachmentPoints[15] << endl;
	cout << "Buffer ID on Depth Attachment 01 = " << attachmentPoints[16] << endl;
	cout << "Buffer ID on Stencil Attachment 01 = " << attachmentPoints[17] << endl;
	
		
	cout << "*****************************************************" << endl;
}
