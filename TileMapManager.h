#include "stdafx.h"

namespace render
{
	#ifndef TILEMAPMANAGER_H
	#define	TILEMAPMANAGER_H

	class TileMapManager: public Object
	{
		private:
		GLuint				vertexBufferStrideCount;
		GLuint				quadFloatCount;
		GLuint				batchDrawOffset;
		GLuint				batchDrawCount;
		GLuint				batchDrawCalls;
		GLuint				textureCounter;
		GLint				maxTextureUnits;
		VertexBufferLayout* ptrvPosLayout;
		VertexBufferLayout* ptrvTexLayout;
		VertexBufferLayout* ptrvShaLayout;
		VertexBufferLayout* ptrvCol1Layout;
		VertexBufferLayout* ptrvCol2Layout;
		VertexBufferLayout* ptrvAlpLayout;
		VertexBufferLayout* ptrvNorLayout;		
		VertexBufferLayout* ptrvTraLayout;
		VertexBufferLayout* ptrvScaLayout;
		VertexBufferLayout* ptrvRotLayout;
		
		IndexBuffer* ptrIndexBuffer;
		VertexBuffer* ptrVertexBuffer;
		VertexArray* ptrVertexArray;

		__declspec(dllexport) void initBuffers();
		__declspec(dllexport) void initLayouts();
		__declspec(dllexport) void updateVertexArray(Sprite* sprite, GLuint offset);
		__declspec(dllexport) void updatePosition(Sprite* sprite, GLuint offset);
		__declspec(dllexport) void updateTexture(Sprite* sprite, GLuint offset);
		__declspec(dllexport) void updateShader(Sprite* sprite, GLuint offset);
		__declspec(dllexport) void updateColor1(Sprite* sprite, GLuint offset);
		__declspec(dllexport) void updateColor2(Sprite* sprite, GLuint offset);
		__declspec(dllexport) void updateAlpha(Sprite* sprite, GLuint offset);
		__declspec(dllexport) void updateNormal(Sprite* sprite, GLuint offset);		
		__declspec(dllexport) void updateTranslate(Sprite* sprite, GLuint offset);
		__declspec(dllexport) void updateScale(Sprite* sprite, GLuint offset);
		__declspec(dllexport) void updateRotate(Sprite* sprite, GLuint offset);
		__declspec(dllexport) void updateEnitities();
		__declspec(dllexport) void updateVertexBuffer();

		public:
		vec2	offset;
		vec2	speed;
		vec2	tileDimension;
		vec2	viewPortDimension;
		vec2	tileMapOffset;
		GLuint	programID;
		GLenum	drawingMode;
		GLuint	mapPageCount;
		GLuint  pageTileCount;
		vec2	tileSeparation;

		vector<Sprite*>	mapTilesArray;
		vector<Sprite*>	pagesTilesArray;
		vector<float>		vertexArray;
		vector<GLuint>		mapData;
		vector<Sprite*>		tilePaletteVector;
		typedef std::map<GLuint, Sprite*, std::less<GLuint> >TilePaletteMap;
		TilePaletteMap		tilePaletteMap;

		__declspec(dllexport) TileMapManager(GLuint tilesPerMap = 224, GLuint tilesPerPage = 224, GLuint* mapTilesData = nullptr, GLuint tileWidth = 16, GLuint tileHeight = 16, GLuint tileSeparationX = 0, GLuint tileSeparationY = 0, GLuint viewPortWidth = 256, GLuint viewPortHeight = 224, GLuint program = 0, GLenum mode = GL_TRIANGLES);
		__declspec(dllexport) ~TileMapManager();
		__declspec(dllexport)void init(GLuint tilesPerMap = 224, GLuint tilesPerPage = 224, GLuint* mapTilesData = nullptr, GLuint tileWidth = 16, GLuint tileHeight = 16, GLuint tileSeparationX = 0, GLuint tileSeparationY = 0, GLuint viewPortWidth = 256, GLuint viewPortHeight = 224, GLuint program = 0, GLenum mode = GL_TRIANGLES);
		__declspec(dllexport)void initMapTilesArray();
		__declspec(dllexport)void batchDraw();
		__declspec(dllexport) void update();
		__declspec(dllexport) void loadPage(GLfloat tileDestinationX = 0, GLfloat tileDestinationY = 0, GLuint pageSource = 0, GLuint pageDestination = 0);
		__declspec(dllexport) void movePage(GLfloat tileDestinationX = 0, GLfloat tileDestinationY = 0, GLuint page = 0);
		__declspec(dllexport)void loadFirstPage(GLuint pageSource = 0);
		__declspec(dllexport) void loadSecondPage(GLuint pageSource = 0);
		__declspec(dllexport) void loadThirdPage(GLuint pageSource = 0);
		__declspec(dllexport)  void loadFourthPage(GLuint pageSource = 0);
		__declspec(dllexport)void print() const;
		__declspec(dllexport)  void printInfo() const;
		__declspec(dllexport) void printVertexArray() const;
		__declspec(dllexport) void printMapTilesArray() const;
		__declspec(dllexport) void printSprites() const;
		__declspec(dllexport)  void printTiles() const;
	};
	#endif // !TILEMAPMANAGER_H
}