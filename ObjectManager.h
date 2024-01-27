
#include "stdafx.h"

#ifndef OBJECTMANAGER_H
#define	OBJECTMANAGER_H

class ObjectManager
{
	private:
	GLuint vertexBufferStrideCount;
	GLuint quadFloatCount;
	GLuint batchDrawOffset;
	GLuint batchDrawCount;
	GLuint batchDrawCalls;
	GLuint textureCounter;
	GLint maxTextureUnits;

	VertexBufferLayout* ptrvPosLayout;
	VertexBufferLayout* ptrvTexLayout;
	VertexBufferLayout* ptrvColLayout;
	VertexBufferLayout* ptrvTraLayout;
	VertexBufferLayout* ptrvScaLayout;
	VertexBufferLayout* ptrvRotLayout;
	IndexBuffer* ptrIndexBuffer;
	VertexBuffer* ptrVertexBuffer;
	VertexArray* ptrVertexArray;

	__declspec(dllexport) 	void updateDataArray(Sprite* sprite, GLuint offset);
	__declspec(dllexport) 	void updatePosition(Sprite *sprite, GLuint offset);
	__declspec(dllexport) void updateTexture(Sprite *sprite, GLuint offset);
	__declspec(dllexport) void updateColor(Sprite *sprite, GLuint offset);
	__declspec(dllexport) void updateTranslate(Sprite *sprite, GLuint offset);
	__declspec(dllexport) void updateScale(Sprite *sprite, GLuint offset);
	__declspec(dllexport) void updateRotate(Sprite *sprite, GLuint offset);
	__declspec(dllexport) void updateEnitities();
	__declspec(dllexport) void updateVertexBuffer();

	public:
	GLuint				programID;
	GLenum				drawingMode;
	vector<Entity *>	entitiesArray;
	vector<float >		dataArray;
	
	__declspec(dllexport) ObjectManager(GLuint program = 0, GLenum mode = GL_TRIANGLES);
	__declspec(dllexport) ~ObjectManager();

	__declspec(dllexport) void	init(GLuint program = 0, GLenum mode = GL_TRIANGLES);
	__declspec(dllexport) void	initDataArray();
	__declspec(dllexport) void	initBuffers();
	__declspec(dllexport) void	initLayouts();
	__declspec(dllexport) void	batchDraw(GLenum mode = GL_TRIANGLES);

	__declspec(dllexport) void update();
	__declspec(dllexport) void print() const;
	__declspec(dllexport) void printInfo() const;
	__declspec(dllexport) void printDataArray() const;
	__declspec(dllexport) void printEntities() const;
};
#endif // !OBJECTMANAGER_H
