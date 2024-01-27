
#include "stdafx.h"

#ifndef VERTEXBUFFERLAYOUT_H
#define	VERTEXBUFFERLAYOUT_H

class VertexBufferLayout
{
	public:
	GLuint			strideSize;
	GLuint			count;
	GLuint			dataType;
	GLboolean		normalize;
	GLuint			attributeLocation;
	const GLchar	*attributeName;
	GLuint			shaderProgramID;

	public:
	__declspec(dllexport) VertexBufferLayout();
	__declspec(dllexport) VertexBufferLayout(GLuint shaderProgramID, const GLchar *attributeName, GLuint count, GLboolean normalize, GLuint strideSize, GLuint offset);
	__declspec(dllexport) ~VertexBufferLayout();

	__declspec(dllexport) void attach();
	__declspec(dllexport) void dettach();
	__declspec(dllexport) void print() const;

};

#endif // !VERTEXBUFFERLAYOUT_H


/*

	template<class T>
	inline VertexBufferLayout<T>::VertexBufferLayout(GLuint shaderProgramID, const GLchar *attributeName, GLuint count, GLboolean normalize, GLvoid *offset)
	{
		attributeLocation = glGetAttribLocation(shaderProgramID, attributeName);
		enable();
		glVertexAttribPointer(attributeLocation, count, GL_FLOAT, normalize, sizeof(GL_FLOAT) * count, offset);
	}

	template<class T>
	inline VertexBufferLayout<T>::VertexBufferLayout(GLuint shaderProgramID, const GLchar *attributeName, GLuint count, GLboolean normalize, GLvoid *offset)
	{
		attributeLocation = glGetAttribLocation(shaderProgramID, attributeName);
		enable();
		glVertexAttribPointer(attributeLocation, count, GL_UNSIGNED_INT, normalize, sizeof(GL_UNSIGNED_INT) * count, offset);
	}


		switch (T)
		{
			case GLbyte:
				glVertexAttribPointer(attributeLocation, count, GL_BYTE, normalize, sizeof(GL_BYTE) * count, offset);
				break;

			case GLuint:

				break;

			case GLfloat:
				glVertexAttribPointer(attributeLocation, count, GL_FLOAT, normalize, sizeof(GL_FLOAT) * count, offset);
				break;

			case GLshort:
				glVertexAttribPointer(attributeLocation, count, GL_SHORT, normalize, sizeof(GL_SHORT) * count, offset);
				break;

			case GLushort:
				glVertexAttribPointer(attributeLocation, count, GL_UNSIGNED_SHORT, normalize, sizeof(GL_UNSIGNED_SHORT) * count, offset);
				break;

			default:
				glVertexAttribPointer(attributeLocation, count, GL_FLOAT, normalize, sizeof(GL_FLOAT) * count, offset);
				break;
		}



	template<class T>
	inline VertexBufferLayout<T>::~VertexBufferLayout()
	{

	}

	template<class T>
	inline void VertexBufferLayout<T>::enable()
	{
		glEnableVertexAttribArray(attributeLocation);
	}

	template<class T>
	inline void VertexBufferLayout<T>::disable()
	{
		glDisableVertexAttribArray(attributeLocation);
	}



	attributeLocation = glGetAttribLocation(shaderProgramID, attributeName);
		enable();

		switch (T)
		{
		case GLbyte:
			glVertexAttribPointer(attributeLocation, count, GL_BYTE, normalize, sizeof(GL_BYTE) * count, offset);
			break;

		case GLuint:
			glVertexAttribPointer(attributeLocation, count, GL_UNSIGNED_INT, normalize, sizeof(GL_UNSIGNED_INT) * count, offset);
			break;

		case GLfloat:
			glVertexAttribPointer(attributeLocation, count, GL_FLOAT, normalize, sizeof(GL_FLOAT) * count, offset);
			break;

		case GLshort:
			glVertexAttribPointer(attributeLocation, count, GL_SHORT, normalize, sizeof(GL_SHORT) * count, offset);
			break;

		case GLushort:
			glVertexAttribPointer(attributeLocation, count, GL_UNSIGNED_SHORT, normalize, sizeof(GL_UNSIGNED_SHORT) * count, offset);
			break;

		default:
			glVertexAttribPointer(attributeLocation, count, GL_FLOAT, normalize, sizeof(GL_FLOAT) * count, offset);
			break;
		};

	*/

