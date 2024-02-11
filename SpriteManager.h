#include "stdafx.h"

namespace render
{
	#ifndef SPRITEMANAGER_H
	#define	SPRITEMANAGER_H

	class SpriteManager: public Object
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
		VertexBufferLayout* ptrvCol1Layout;
		VertexBufferLayout* ptrvCol2Layout;
		VertexBufferLayout* ptrvAlphaLayout;
		VertexBufferLayout* ptrvNormallLayout;
		VertexBufferLayout* ptrvShaderLayout;
		VertexBufferLayout* ptrvTraLayout;
		VertexBufferLayout* ptrvScaLayout;
		VertexBufferLayout* ptrvRotLayout;
		IndexBuffer*		ptrIndexBuffer;
		VertexBuffer*		ptrVertexBuffer;
		VertexArray*		ptrVertexArray;

		__declspec(dllexport) void updateDataArray(Sprite* sprite, GLuint offset);
		__declspec(dllexport) void updatePosition(Sprite* sprite, GLuint offset);
		__declspec(dllexport) void updateTexture(Sprite* sprite, GLuint offset);
		__declspec(dllexport) void updateColor1(Sprite* sprite, GLuint offset);
		__declspec(dllexport) void updateColor2(Sprite* sprite, GLuint offset);
		__declspec(dllexport) void updateAlpha(Sprite* sprite, GLuint offset);
		__declspec(dllexport) void updateNormal(Sprite* sprite, GLuint offset);
		__declspec(dllexport) void updateShader(Sprite* sprite, GLuint offset);
		__declspec(dllexport) void updateTranslate(Sprite* sprite, GLuint offset);
		__declspec(dllexport) void updateScale(Sprite* sprite, GLuint offset);
		__declspec(dllexport) void updateRotate(Sprite* sprite, GLuint offset);
		__declspec(dllexport) void updateEnitities();
		__declspec(dllexport) void updateVertexBuffer();

		public:
		GLuint				programID;
		GLenum				drawingMode;
		vector<Entity*>		entitiesArray;
		vector<float >		dataArray;

		__declspec(dllexport) SpriteManager(GLuint program = 0, GLenum mode = GL_TRIANGLES);
		__declspec(dllexport) ~SpriteManager();

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
#endif // !SPRITEMANAGER_H
}