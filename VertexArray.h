
#include "stdafx.h"

#ifndef VERTEXARRAY_H
#define	VERTEXARRAY_H

class VertexArray
{
public:
	GLuint	vertexArrayID;

public:
	__declspec(dllexport) 	  VertexArray();
	__declspec(dllexport) ~VertexArray();

	__declspec(dllexport) 	  void init();
	__declspec(dllexport) void attach() const;
	__declspec(dllexport) void detach() const;
};
#endif // !VERTEXBUFFER_H
#pragma once
