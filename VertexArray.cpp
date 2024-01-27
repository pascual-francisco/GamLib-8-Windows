
#include "stdafx.h"

VertexArray::VertexArray()
{
	vertexArrayID = 0;
	init();
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &vertexArrayID);
}

void VertexArray::init()
{
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);
}

void VertexArray::attach() const
{
	glBindVertexArray(vertexArrayID);
}

void VertexArray::detach() const
{
	glBindVertexArray(0);
}
