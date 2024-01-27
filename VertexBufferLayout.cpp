
#include "stdafx.h"

VertexBufferLayout::VertexBufferLayout()
{
	count = 0;
	dataType = GL_FLOAT;
	normalize = false;
	attributeLocation = 0;
	attributeName = "name";
	shaderProgramID = 0;
	strideSize = 0;
}

VertexBufferLayout::VertexBufferLayout(GLuint id, const GLchar *nam, GLuint cou, GLboolean nor, GLuint str, GLuint off)
{
	shaderProgramID = id;
	attributeName = nam;
	count = cou;
	normalize = nor;
	strideSize = str;
	dataType = GL_FLOAT;

	attributeLocation = glGetAttribLocation(shaderProgramID, attributeName);
	glEnableVertexAttribArray(attributeLocation);
	glVertexAttribPointer(attributeLocation, count, dataType, normalize, sizeof(dataType) * strideSize, (const void *) off);
}

VertexBufferLayout::~VertexBufferLayout()
{

}

void VertexBufferLayout::attach()
{
	glEnableVertexAttribArray(attributeLocation);
}

void VertexBufferLayout::dettach()
{
	glDisableVertexAttribArray(attributeLocation);
}

void VertexBufferLayout::print() const
{
	cout << "*****************************************************" << endl;
	cout << "Vertex Buffer Layout Info:" << endl;
	cout << "Program ID = "<<shaderProgramID << endl;
	cout << "Stride Size = " << strideSize << endl;
	cout << "Count = " << count << endl;

	cout << "Normalize = ";
	if(normalize == GL_FALSE)
		cout << "False" << endl;

	if (normalize == GL_TRUE)
		cout << "True" << endl;

	cout << "Data Type = ";
	if (dataType == GL_FLOAT)
		cout << "GL_FLOAT" << endl;

	if (dataType == GL_BYTE)
		cout << "GL_FLOAT" << endl;

	if (dataType == GL_UNSIGNED_BYTE)
		cout << "GL_UNSIGNED_BYTE" << endl;

	if (dataType == GL_SHORT)
		cout << "GL_SHORT" << endl;

	if (dataType == GL_UNSIGNED_SHORT)
		cout << "GL_UNSIGNED_SHORT" << endl;

	if (dataType == GL_INT)
		cout << "GL_INT" << endl;

	if (dataType == GL_UNSIGNED_INT)
		cout << "GL_UNSIGNED_INT" << endl;

	cout << "*****************************************************" << endl;
}
