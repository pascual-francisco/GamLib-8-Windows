
#include "stdafx.h"

TileMapManager::TileMapManager(GLuint tilesPerMap, GLuint tilesPerPage, GLuint* mapTilesData, GLuint tileWidth, GLuint tileHeight, GLuint tileSeparationX, GLuint tileSeparationY, GLuint viewPortWidth, GLuint viewPortHeight, GLuint program, GLenum mode)
{
	ptrvPosLayout = nullptr;
	ptrvTexLayout = nullptr;
	ptrvColLayout = nullptr;
	ptrvTraLayout = nullptr;
	ptrvScaLayout = nullptr;
	ptrvRotLayout = nullptr;
	ptrVertexBuffer = nullptr;
	ptrVertexArray = nullptr;
	ptrIndexBuffer = nullptr;

	batchDrawCount = 0;
	batchDrawCalls = 0;
	textureCounter = 0;

	offset = vec2(0.0f, 0.0f);
	speed = vec2(0.0f, 0.0f);
	mapPageCount = 0;
	pageTileCount = 0;

	init(tilesPerMap, tilesPerPage, mapTilesData, tileWidth, tileHeight, tileSeparationX, tileSeparationY, viewPortWidth, viewPortHeight, program, mode);
}

void TileMapManager::init(GLuint tilesPerMap, GLuint tilesPerPage, GLuint* mapTilesData, GLuint tileWidth, GLuint tileHeight, GLuint tileSeparationX, GLuint tileSeparationY, GLuint viewPortWidth, GLuint viewPortHeight, GLuint program, GLenum mode)
{
	vertexBufferStrideCount = 20;
	quadFloatCount = 80;
	programID = program;
	tileDimension = vec2(tileWidth, tileHeight);
	viewPortDimension = vec2(viewPortWidth, viewPortHeight);
	drawingMode = mode;
	maxTextureUnits = 0;
	tileSeparation = vec2(tileSeparationX, tileSeparationY);

	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureUnits);
	batchDrawOffset = maxTextureUnits * 6;
	pageTileCount = tilesPerPage;
	mapPageCount = tilesPerMap / pageTileCount;

	mapTilesArray = vector<Sprite*>(tilesPerMap);
	pagesTilesArray = vector<Sprite*>(pageTileCount * 4);
	vertexArray = vector<float>(pagesTilesArray.size() * vertexBufferStrideCount * 4);
	tilePaletteMap = TilePaletteMap();

	vector<Sprite*>::iterator mtit;
	vector<Sprite*>::iterator tait;
	vector<float >::iterator vait;

	//Init 4 pages of tiles for copy to vertex buffer
	if (pagesTilesArray.size() > 0)
	{
		for (tait = pagesTilesArray.begin(); tait != pagesTilesArray.end(); tait++)
			(*tait) = new Sprite();
	}

	//Create data array for updates
	if (vertexArray.size() > 0)
	{
		for (vait = vertexArray.begin(); vait != vertexArray.end(); vait++)
			(*vait) = 0.0f;
	}

	if (mapTilesArray.size() > 0)
	{
		uint i = 0;

		for (mtit = mapTilesArray.begin(); mtit != mapTilesArray.end(); mtit++)
		{
			(*mtit) = new Sprite(mapTilesData[i]);
			i++;
		}
	}

	


	initBuffers();
	initLayouts();
	updateEnitities();
}

TileMapManager::~TileMapManager()
{
	delete ptrVertexBuffer;
	delete ptrVertexArray;
	delete ptrIndexBuffer;
	delete ptrvPosLayout;
	delete ptrvTexLayout;
	delete ptrvColLayout;
	delete ptrvTraLayout;
	delete ptrvScaLayout;
	delete ptrvRotLayout;
	tilePaletteVector.clear();
	mapTilesArray.clear();
	pagesTilesArray.clear();
	vertexArray.clear();
}

void TileMapManager::initMapTilesArray()
{
	vector<Sprite*>::iterator mtit;

	if (mapTilesArray.size() > 0)
	{
		for (mtit = mapTilesArray.begin(); mtit != mapTilesArray.end(); mtit++)
		{
			if (tilePaletteMap.size() > 0)
			{
				if (tilePaletteMap.at((*mtit)->spriteID) != NULL)
				{
					(*mtit) = new Sprite(*tilePaletteMap.at((*mtit)->spriteID));
				}
			}
		}
	}
}

void TileMapManager::initBuffers()
{
	//Vertex Array//
	ptrVertexArray = new VertexArray();

	//Vertex Buffer//
	ptrVertexBuffer = new VertexBuffer(vertexArray.size(), sizeof(GLfloat), vertexArray.data());

	//Index Buffer//
	ptrIndexBuffer = new IndexBuffer(6 * pageTileCount * 4, sizeof(GL_UNSIGNED_INT), nullptr);

	batchDrawCalls = ptrIndexBuffer->bufferCount / batchDrawOffset;
}

void TileMapManager::initLayouts()
{
	/*
	DATA BUFFER:
	Entity 0
		Sprite 0
		[XYZSTPQRGBATTTSSSRRR]
		[XYZSTRQRGBATTTSSSRRR]
		[XYZSTRQRGBATTTSSSRRR]
		[XYZSTRQRGBATTTSSSRRR]
		= 20 Floats
		20 Float * 4 Vertices = 80 Floats
		1 Quad = 80 Floats
	*/
	ptrvPosLayout = new VertexBufferLayout(programID, "vs_vertex_position", 3, GL_FALSE, 20, 0 * 4);
	ptrvTexLayout = new VertexBufferLayout(programID, "vertex_texture_coords", 4, GL_FALSE, 20, 3 * 4);
	ptrvColLayout = new VertexBufferLayout(programID, "vertex_color", 4, GL_FALSE, 20, 7 * 4);
	ptrvTraLayout = new VertexBufferLayout(programID, "vertex_translate", 3, GL_FALSE, 20, 11 * 4);
	ptrvScaLayout = new VertexBufferLayout(programID, "vertex_scale", 3, GL_FALSE, 20, 14 * 4);
	ptrvRotLayout = new VertexBufferLayout(programID, "vertex_rotate", 3, GL_FALSE, 20, 17 * 4);

	ptrVertexArray->detach();
	ptrVertexBuffer->detach();
	ptrIndexBuffer->detach();
}

void TileMapManager::update()
{
	offset.x = offset.x + speed.x;
	offset.y = offset.y + speed.y;

	updateEnitities();
	updateVertexBuffer();
}



void TileMapManager::loadPage(GLfloat tileDestinationX, GLfloat tileDestinationY, GLuint pageSource, GLuint pageDestination)
{
	uint tw = viewPortDimension.x / tileDimension.x;
	uint th = viewPortDimension.y / tileDimension.x;

	uint w = 0;
	uint h = th - 1;

	for (uint i = 0; i < pageTileCount; i++)
	{
		pagesTilesArray[i + (pageTileCount * pageDestination)] = new Sprite(*mapTilesArray[i + (pageTileCount * pageSource)]);
		pagesTilesArray[i + (pageTileCount * pageDestination)]->transformation.translate.x = (w * tileDimension.x) + (tileDestinationX * tileDimension.x);
		pagesTilesArray[i + (pageTileCount * pageDestination)]->transformation.translate.y = (h * tileDimension.y) + (tileDestinationY * tileDimension.y);

		if (w < (tw - 1))
		{
			w++;
		}

		else
		{
			w = 0;
			h--;
		}


	}
}

void TileMapManager::movePage(GLfloat tileDestinationX, GLfloat tileDestinationY, GLuint page)
{
	uint tw = viewPortDimension.x / tileDimension.x;
	uint th = viewPortDimension.y / tileDimension.y;

	uint w = 0;
	uint h = th - 1;

	for (uint i = 0; i < pageTileCount; i++)
	{
		pagesTilesArray[i + (pageTileCount * page)]->transformation.translate.x = (w * tileDimension.x) + (tileDestinationX * tileDimension.x);
		pagesTilesArray[i + (pageTileCount * page)]->transformation.translate.y = (h * tileDimension.y) + (tileDestinationY * tileDimension.y);

		if (w < (tw - 1))
		{
			w++;
		}

		else
		{
			w = 0;
			h--;
		}
	}
}

void TileMapManager::loadFirstPage(GLuint pageSource)
{
	loadPage(0, 0, pageSource, 0);
}

void TileMapManager::loadSecondPage(GLuint pageSource)
{
	loadPage(16, 0, pageSource, 1);
}

void TileMapManager::loadThirdPage(GLuint pageSource)
{
	loadPage(0, -15, pageSource, 2);
}

void TileMapManager::loadFourthPage(GLuint pageSource)
{
	loadPage(16, -15, pageSource, 3);
}

void TileMapManager::updateEnitities()
{
	GLuint offset = 0;
	vector<Sprite*>::iterator tait;

	if (pagesTilesArray.size() > 0)
	{
		for (tait = pagesTilesArray.begin(); tait != pagesTilesArray.end(); tait++)
		{
			
			//Update all sprites
			(*tait)->update();

			//Copy data from Entities array to data array of floats
			updateVertexArray(*tait, offset);

			//Apply offset
			offset += quadFloatCount;
		}
	}
}

void TileMapManager::updateVertexArray(Sprite* sprite, GLuint offset)
{
	updatePosition(sprite, offset + 0);
	updateTexture(sprite, offset + 3);
	updateColor(sprite, offset + 7);
	updateTranslate(sprite, offset + 11);
	updateScale(sprite, offset + 14);
	updateRotate(sprite, offset + 17);
}

void TileMapManager::updatePosition(Sprite* sprite, GLuint offset)
{
	//glVertex3f(-image->pivotX.value, -image->pivotY.value, -image->pivotZ.value);
	vertexArray[offset] = -sprite->transformation.pivot.x;
	offset++;
	vertexArray[offset] = -sprite->transformation.pivot.y;
	offset++;
	vertexArray[offset] = -sprite->transformation.pivot.z;
	offset += (20 - 2);

	//glVertex3f(float(pImage->w) - image->pivotX.value, -image->pivotY.value, -image->pivotZ.value);
	vertexArray[offset] = sprite->textureOffset.p - sprite->transformation.pivot.x;
	offset++;
	vertexArray[offset] = -sprite->transformation.pivot.y;
	offset++;
	vertexArray[offset] = -sprite->transformation.pivot.z;
	offset += (20 - 2);

	//glVertex3f(float(pImage->w) - image->pivotX.value, float(pImage->h) - image->pivotY.value, -image->pivotZ.value);
	vertexArray[offset] = sprite->textureOffset.p - sprite->transformation.pivot.x;
	offset++;
	vertexArray[offset] = sprite->textureOffset.q - sprite->transformation.pivot.y;
	offset++;
	vertexArray[offset] = -sprite->transformation.pivot.z;
	offset += (20 - 2);

	//glVertex3f(-image->pivotX.value, float(pImage->h) - image->pivotY.value, -image->pivotZ.value)
	vertexArray[offset] = -sprite->transformation.pivot.x;
	offset++;
	vertexArray[offset] = sprite->textureOffset.q - sprite->transformation.pivot.y;
	offset++;
	vertexArray[offset] = -sprite->transformation.pivot.z;
}

void TileMapManager::updateTexture(Sprite* sprite, GLuint offset)
{
	vec3 pageDimension = vec3(0.0f, 0.0f, 0.0f);
	vec3 texturePosition = vec3(0.0f, 0.0f, 0.0f);
	vec3 textureDimension = vec3(0.0f, 0.0f, 0.0f);

	glBindTexture(GL_TEXTURE_2D_ARRAY, sprite->texturePalette);
	glGetTexLevelParameterfv(GL_TEXTURE_2D_ARRAY, 0, GL_TEXTURE_WIDTH, &pageDimension.x);
	glGetTexLevelParameterfv(GL_TEXTURE_2D_ARRAY, 0, GL_TEXTURE_HEIGHT, &pageDimension.y);
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

	textureDimension.x = sprite->textureOffset.p / pageDimension.x;
	textureDimension.y = sprite->textureOffset.q / pageDimension.y;
	textureDimension.z = sprite->palettePage;

	if (sprite->ptrAnimation->lastFrame == 0)
	{
		texturePosition.s = (sprite->textureOffset.s / pageDimension.x) + sprite->tileIndex.s * (textureDimension.x * 1 + (sprite->tileSeparation.s / pageDimension.x));
		texturePosition.t = (sprite->textureOffset.t / pageDimension.y) + sprite->tileIndex.t * (textureDimension.y * 1 + (sprite->tileSeparation.t / pageDimension.y));
		pageDimension.z = sprite->palettePage;
	}
	else
	{
		if (sprite->animationDirection == Animation::WIDTH)
		{
			//texturePosition.s = (sprite->textureOffset.s / pageDimension.x) + sprite->ptrAnimation->actualFrame * textureDimension.x + sprite->ptrAnimation->actualFrame * (sprite->tileSeparation.s / pageDimension.x);
			texturePosition.s = (sprite->textureOffset.s / pageDimension.x) + sprite->ptrAnimation->keyFrames[sprite->ptrAnimation->actualFrame] * textureDimension.x + sprite->ptrAnimation->keyFrames[sprite->ptrAnimation->actualFrame] * (sprite->tileSeparation.s / pageDimension.x);
			texturePosition.t = sprite->textureOffset.t / pageDimension.y;
			pageDimension.z = sprite->palettePage;
			textureDimension.z = sprite->palettePage;			
		}

		if (sprite->animationDirection == Animation::HEIGHT)
		{
			texturePosition.s = sprite->textureOffset.s / pageDimension.x;
			//texturePosition.t = (sprite->textureOffset.t / pageDimension.y) + sprite->ptrAnimation->actualFrame * textureDimension.y + sprite->ptrAnimation->actualFrame * (sprite->tileSeparation.t / pageDimension.y);
			texturePosition.t = (sprite->textureOffset.t / pageDimension.y) + sprite->ptrAnimation->keyFrames[sprite->ptrAnimation->actualFrame] * textureDimension.y + sprite->ptrAnimation->keyFrames[sprite->ptrAnimation->actualFrame] * (sprite->tileSeparation.t / pageDimension.y);
			pageDimension.z = sprite->palettePage;
			textureDimension.z = sprite->palettePage;
		}

		if (sprite->animationDirection == Animation::DEPTH_NORMALIZED)
		{
			texturePosition.s = 0.0f;
			texturePosition.t = 0.0f;
			sprite->textureOffset.p = pageDimension.x;
			sprite->textureOffset.q = pageDimension.y;
			//pageDimension.z = sprite->ptrAnimation->actualFrame;
			//textureDimension.z = sprite->ptrAnimation->actualFrame;
			pageDimension.z = sprite->ptrAnimation->keyFrames[sprite->ptrAnimation->actualFrame];
			textureDimension.z = sprite->ptrAnimation->keyFrames[sprite->ptrAnimation->actualFrame];
		}

		if (sprite->animationDirection == Animation::DEPTH_DENORMALIZED)
		{
			texturePosition.s = 0.0f;
			texturePosition.t = 0.0f;
			//pageDimension.z = sprite->ptrAnimation->actualFrame;
			//textureDimension.z = sprite->ptrAnimation->actualFrame;
			pageDimension.z = sprite->ptrAnimation->keyFrames[sprite->ptrAnimation->actualFrame];
			textureDimension.z = sprite->ptrAnimation->keyFrames[sprite->ptrAnimation->actualFrame];
		}
	}

	//image->textureX.value	
	vertexArray[offset] = texturePosition.s;
	offset++;
	//image->textureY.value + image->textureHeight.value	
	vertexArray[offset] = texturePosition.t + textureDimension.y;
	offset++;
	vertexArray[offset] = pageDimension.z;
	offset++;
	vertexArray[offset] = GLfloat(sprite->texturePalette);
	offset += (20 - 3);

	//image->textureX.value + image->textureWidth.value	
	vertexArray[offset] = texturePosition.s + textureDimension.x;
	offset++;
	//image->textureY.value + image->textureHeight.value);	
	vertexArray[offset] = texturePosition.t + textureDimension.y;
	offset++;
	vertexArray[offset] = pageDimension.z;
	offset++;
	vertexArray[offset] = GLfloat(sprite->texturePalette);
	offset += (20 - 3);

	//image->textureX.value + image->textureWidth.value	
	vertexArray[offset] = texturePosition.s + textureDimension.x;
	offset++;
	//image->textureY.value	
	vertexArray[offset] = texturePosition.t;
	offset++;
	vertexArray[offset] = pageDimension.z;
	offset++;
	vertexArray[offset] = GLfloat(sprite->texturePalette);
	offset += (20 - 3);

	//image->textureX.value	
	vertexArray[offset] = texturePosition.s;
	offset++;
	//image->textureY.value
	vertexArray[offset] = texturePosition.t;
	offset++;
	vertexArray[offset] = pageDimension.z;
	offset++;
	vertexArray[offset] = GLfloat(sprite->texturePalette);
}

void TileMapManager::updateColor(Sprite* sprite, GLuint offset)
{
	vertexArray[offset] = sprite->vertexColor[0].r;
	offset++;
	vertexArray[offset] = sprite->vertexColor[0].g;
	offset++;
	vertexArray[offset] = sprite->vertexColor[0].b;
	offset++;
	vertexArray[offset] = sprite->vertexColor[0].a;
	offset += (20 - 3);

	vertexArray[offset] = sprite->vertexColor[1].r;
	offset++;
	vertexArray[offset] = sprite->vertexColor[1].g;
	offset++;
	vertexArray[offset] = sprite->vertexColor[1].b;
	offset++;
	vertexArray[offset] = sprite->vertexColor[1].a;
	offset += (20 - 3);

	vertexArray[offset] = sprite->vertexColor[2].r;
	offset++;
	vertexArray[offset] = sprite->vertexColor[2].g;
	offset++;
	vertexArray[offset] = sprite->vertexColor[2].b;
	offset++;
	vertexArray[offset] = sprite->vertexColor[2].a;
	offset += (20 - 3);

	vertexArray[offset] = sprite->vertexColor[3].r;
	offset++;
	vertexArray[offset] = sprite->vertexColor[3].g;
	offset++;
	vertexArray[offset] = sprite->vertexColor[3].b;
	offset++;
	vertexArray[offset] = sprite->vertexColor[3].a;
}

void TileMapManager::updateTranslate(Sprite* sprite, GLuint offset)
{
	vertexArray[offset] = sprite->transformation.translate.x + this->offset.x;
	offset++;
	vertexArray[offset] = sprite->transformation.translate.y + this->offset.y;
	offset++;
	vertexArray[offset] = sprite->transformation.translate.z;
	offset += (20 - 2);

	vertexArray[offset] = sprite->transformation.translate.x + this->offset.x;
	offset++;
	vertexArray[offset] = sprite->transformation.translate.y + this->offset.y;
	offset++;
	vertexArray[offset] = sprite->transformation.translate.z;
	offset += (20 - 2);

	vertexArray[offset] = sprite->transformation.translate.x + this->offset.x;
	offset++;
	vertexArray[offset] = sprite->transformation.translate.y + this->offset.y;
	offset++;
	vertexArray[offset] = sprite->transformation.translate.z;
	offset += (20 - 2);

	vertexArray[offset] = sprite->transformation.translate.x + this->offset.x;
	offset++;
	vertexArray[offset] = sprite->transformation.translate.y + this->offset.y;
	offset++;
	vertexArray[offset] = sprite->transformation.translate.z;


}

void TileMapManager::updateScale(Sprite* sprite, GLuint offset)
{
	vertexArray[offset] = sprite->transformation.scale.x;
	offset++;
	vertexArray[offset] = sprite->transformation.scale.y;
	offset++;
	vertexArray[offset] = sprite->transformation.scale.z;
	offset += (20 - 2);

	vertexArray[offset] = sprite->transformation.scale.x;
	offset++;
	vertexArray[offset] = sprite->transformation.scale.y;
	offset++;
	vertexArray[offset] = sprite->transformation.scale.z;
	offset += (20 - 2);

	vertexArray[offset] = sprite->transformation.scale.x;
	offset++;
	vertexArray[offset] = sprite->transformation.scale.y;
	offset++;
	vertexArray[offset] = sprite->transformation.scale.z;
	offset += (20 - 2);

	vertexArray[offset] = sprite->transformation.scale.x;
	offset++;
	vertexArray[offset] = sprite->transformation.scale.y;
	offset++;
	vertexArray[offset] = sprite->transformation.scale.z;
}

void TileMapManager::updateRotate(Sprite* sprite, GLuint offset)
{
	vertexArray[offset] = sprite->transformation.rotate.x;
	offset++;
	vertexArray[offset] = sprite->transformation.rotate.y;
	offset++;
	vertexArray[offset] = sprite->transformation.rotate.z;
	offset += (20 - 2);

	vertexArray[offset] = sprite->transformation.rotate.x;
	offset++;
	vertexArray[offset] = sprite->transformation.rotate.y;
	offset++;
	vertexArray[offset] = sprite->transformation.rotate.z;
	offset += (20 - 2);

	vertexArray[offset] = sprite->transformation.rotate.x;
	offset++;
	vertexArray[offset] = sprite->transformation.rotate.y;
	offset++;
	vertexArray[offset] = sprite->transformation.rotate.z;
	offset += (20 - 2);

	vertexArray[offset] = sprite->transformation.rotate.x;
	offset++;
	vertexArray[offset] = sprite->transformation.rotate.y;
	offset++;
	vertexArray[offset] = sprite->transformation.rotate.z;
}

void TileMapManager::updateVertexBuffer()
{
	ptrVertexBuffer->attach();
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertexArray.size() * sizeof(GLfloat), vertexArray.data());
	ptrVertexBuffer->detach();
}

void TileMapManager::batchDraw()
{
	ptrVertexArray->attach();
	ptrVertexBuffer->attach();
	ptrIndexBuffer->attach();

	//Define offset to texture unit on vertex buffer
	GLuint offset = 6;
	//Draw vertices in groups of 32
	for (uint i = 0; i < batchDrawCalls; i++)
	{
		//Bind each quad texture to 32 texture units
		for (int j = 0; j < maxTextureUnits; j++)
		{
			glActiveTexture(GL_TEXTURE0 + GLuint(vertexArray[offset]));
			glBindTexture(GL_TEXTURE_2D_ARRAY, GLuint(vertexArray[offset]));

			for (uint k = 0; k < 4; k++)
			{
				batchDrawCount = i;
				textureCounter = j;
				vertexArray[offset] = j;
				offset += (vertexBufferStrideCount);
			}
		}
		glDrawRangeElements(drawingMode, i * batchDrawOffset, (i * batchDrawOffset) + batchDrawOffset, ptrIndexBuffer->bufferCount, GL_UNSIGNED_INT, 0);
	}
	ptrVertexArray->detach();
	ptrVertexBuffer->detach();
	ptrIndexBuffer->detach();
}

void TileMapManager::print() const
{
	printInfo();
	printSprites();
	printVertexArray();
	printMapTilesArray();
	printSprites();
}

void TileMapManager::printInfo() const
{
	cout << "**************************************************" << endl;
	cout << "Tile Map Manager Info:" << endl;
	cout << "Offset X = " << offset.x << endl;
	cout << "Offset Y = " << offset.y << endl;
	cout << "Map Page Count = " << mapPageCount << endl;
	cout << "Page Tile Count = " << pageTileCount << endl;
	cout << "Batch Draw Calls = " << batchDrawCalls << endl;
	cout << "Batch Draw Offset = " << batchDrawOffset << endl;
	cout << "Entities Buffer Size = " << pagesTilesArray.size() << endl;
	cout << "Data Buffer Size = " << vertexArray.size() << endl;
	cout << "Quad Count = " << vertexArray.size() / vertexBufferStrideCount << endl;
	cout << "Quad Float Count = " << quadFloatCount << endl;
	cout << "Vertex Buffer Stride Count = " << vertexBufferStrideCount << endl;
	cout << "**************************************************" << endl;
}

void TileMapManager::printVertexArray() const
{
	cout << "******************************************************************************************************************************************************************************" << endl;
	cout << "Buffer Data: " << endl;
	cout << "X---Y---Z---S---T---P---Q---R---G---B---A---Tx---Ty---Tz---Sx---Sy---Sz---Rx---Ry---Rz" << endl;

	for (uint i = 0; i < vertexArray.size(); i++)
	{
		if (i > 0)
		{
			if (i % vertexBufferStrideCount == 0)
				cout << endl;
		}
		cout << vertexArray[i] << ", ";
	}

	cout << endl << "Buffer Data: " << endl;
	cout << "******************************************************************************************************************************************************************************" << endl;
}

void TileMapManager::printMapTilesArray() const
{
	cout << "******************************************************************************************************************************************************************************" << endl;
	cout << "Map Tiles Data: " << endl;
	for (uint i = 0; i < mapTilesArray.size(); i++)
	{
		if (i > 0)
		{
			if (i % vertexBufferStrideCount == 0)
				cout << endl;
		}
		cout << mapTilesArray[i] << ",";
	}

	cout << endl << "Map Tiles Data: " << endl;
	cout << "******************************************************************************************************************************************************************************" << endl;
}

void TileMapManager::printSprites() const
{
	cout << "**************************************************" << endl;
	cout << "Buffer Sprites: " << endl;

	for (GLuint i = 0; i < pagesTilesArray.size(); i++)
		pagesTilesArray[i]->print();

	cout << "Buffer Sprites: " << endl;
	cout << "**************************************************" << endl;
}

void TileMapManager::printTiles() const
{
	cout << "******************************************************************************************************************************************************************************" << endl;
	cout << "Tile Map Sprites: " << endl;

	uint w = 0;

	for (uint i = 0; i < pagesTilesArray.size(); i++)
	{
		cout << "[ " << pagesTilesArray[i]->tileIndex.x << "," << pagesTilesArray[i]->tileIndex.y << " ]";

		if (w < ((viewPortDimension.x / tileDimension.x) - 1))
			w++;
		else
		{
			w = 0;
			cout << "," << endl;
		}
	}
	cout << "Tile Map Sprites: " << endl;
	cout << "******************************************************************************************************************************************************************************" << endl;
}


