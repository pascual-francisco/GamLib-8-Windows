
#include "stdafx.h"

#ifndef	UNIFORMBUFFER_H
#define	UNIFORMBUFFER_H

class UniformBuffer: public BufferObject
{
public:
	const GLchar	**names;
	const void		*data;
	GLsizei			dataSize;
	GLuint			shaderProgramID;
	GLuint			uniformBufferID;
	GLuint			blockSize;
	GLuint			blockIndex;
	GLuint			*offsets;
	GLuint			*indices;
	GLuint			*sizes;
	GLsizei			memberCount;

public:
__declspec(dllexport) UniformBuffer();
__declspec(dllexport) UniformBuffer(GLuint program, GLsizei count,       const void *data, GLsizei size);
__declspec(dllexport) ~UniformBuffer();
__declspec(dllexport) void init(GLuint program, GLsizei count, const void *data, GLsizei size);
__declspec(dllexport) void initUniformIndices();
__declspec(dllexport) void initUniformLocations();
__declspec(dllexport) void attach() const;
__declspec(dllexport) void detach() const;
};
#endif // !VERTEXBUFFER_H
#pragma once
