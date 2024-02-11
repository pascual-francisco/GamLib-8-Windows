#include "stdafx.h"

namespace render
{

	SpriteManager::SpriteManager(GLuint program, GLenum mode)
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
		init(program, mode);

		Sprite* spr;
		spr = new Sprite();
	}

	SpriteManager::~SpriteManager()
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
		entitiesArray.clear();
		dataArray.clear();
	}

	void SpriteManager::init(GLuint program, GLenum mode)
	{
		programID = program;
		drawingMode = mode;
		maxTextureUnits = 0;
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureUnits);
		batchDrawOffset = maxTextureUnits * 6;
		batchDrawCount = 0;
		batchDrawCalls = 0;
		textureCounter = 0;
		vertexBufferStrideCount = 20;
		quadFloatCount = 80;
	}

	void SpriteManager::initDataArray()
	{
		GLuint sprites = 0;
		GLuint vertices = 4;

		vector<Entity*>::iterator eit;
		vector<Sprite*>::iterator sit;
		vector<float >::iterator dit;

		if (entitiesArray.size() > 0)
		{
			for (eit = entitiesArray.begin(); eit != entitiesArray.end(); eit++)
			{
				if ((*eit) != nullptr)
				{
					for (sit = (*eit)->sprite.begin(); sit != (*eit)->sprite.end(); sit++)
					{
						if ((*sit) != nullptr)
						{
							sprites++;
						}
					}
				}
			}
		}

		dataArray = vector<float>(sprites * vertices * vertexBufferStrideCount);

		initBuffers();
		initLayouts();
		updateEnitities();
	}

	void SpriteManager::initBuffers()
	{
		//Vertex Array//
		ptrVertexArray = new VertexArray();

		//Vertex Buffer//
		ptrVertexBuffer = new VertexBuffer(dataArray.size(), sizeof(GLfloat), dataArray.data());

		//Index Buffer//
		ptrIndexBuffer = new IndexBuffer(6 * (dataArray.size() / quadFloatCount), sizeof(GL_UNSIGNED_INT), nullptr);

		batchDrawCalls = ptrIndexBuffer->bufferCount / batchDrawOffset;
	}

	void SpriteManager::initLayouts()
	{
		/*
		DATA BUFFER:
		Entity 0
			Sprite 0 [XYZ-STPQ-RGBA-TTT-SSS-RRR] , [XYZ-STRQ-RGBA-TTT-SSS-RRR] , [XYZ-STRQ-RGBA-TTT-SSS-RRR] , [XYZ-STRQ-RGBA-TTT-SSS-RRR] = 20 Floats
			20 Float * 4 Vertices = 84 Floats
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

	void SpriteManager::updateEnitities()
	{
		GLuint offset = 0;

		vector<Entity*>::iterator eit;
		vector<Sprite*>::iterator sit;

		if (entitiesArray.size() > 0)
		{
			for (eit = entitiesArray.begin(); eit != entitiesArray.end(); eit++)
			{
				if ((*eit) != nullptr)
				{
					if ((*eit)->active)
					{
						(*eit)->update();

						(*eit)->mechanics.speed.x += (*eit)->mechanics.acceleration.x;
						(*eit)->mechanics.speed.y += (*eit)->mechanics.acceleration.y;

						(*eit)->mechanics.position.x += (*eit)->mechanics.speed.x;
						(*eit)->mechanics.position.y += (*eit)->mechanics.speed.y;

						if ((*eit)->sprite.size() > 0)
						{
							for (sit = (*eit)->sprite.begin(); sit != (*eit)->sprite.end(); sit++)
							{
								if ((*eit)->active)
								{
									(*sit)->transformation.translate.x = (*sit)->positionOffset.x + (*eit)->mechanics.position.x;
									(*sit)->transformation.translate.y = (*sit)->positionOffset.y + (*eit)->mechanics.position.y;
									(*sit)->update();
									updateDataArray(*sit, offset);
									offset += quadFloatCount;
								}
							}
						}
					}
				}
			}
		}
	}

	void SpriteManager::updateVertexBuffer()
	{
		ptrVertexBuffer->attach();
		glBufferSubData(GL_ARRAY_BUFFER, 0, dataArray.size() * sizeof(GLfloat), dataArray.data());
		ptrVertexBuffer->detach();
	}

	void SpriteManager::updateDataArray(Sprite* sprite, GLuint offset)
	{
		updatePosition(sprite, offset + 0);
		updateTexture(sprite, offset + 3);
		updateColor(sprite, offset + 7);
		updateTranslate(sprite, offset + 11);
		updateScale(sprite, offset + 14);
		updateRotate(sprite, offset + 17);
	}

	void SpriteManager::updatePosition(Sprite* sprite, GLuint offset)
	{
		//glVertex3f(-image->pivotX.value, -image->pivotY.value, -image->pivotZ.value);
		dataArray[offset] = -sprite->transformation.pivot.x;
		offset++;
		dataArray[offset] = -sprite->transformation.pivot.y;
		offset++;
		dataArray[offset] = -sprite->transformation.pivot.z;
		offset += (20 - 2);

		//glVertex3f(float(pImage->w) - image->pivotX.value, -image->pivotY.value, -image->pivotZ.value);
		dataArray[offset] = sprite->textureOffset.p - sprite->transformation.pivot.x;
		offset++;
		dataArray[offset] = -sprite->transformation.pivot.y;
		offset++;
		dataArray[offset] = -sprite->transformation.pivot.z;
		offset += (20 - 2);

		//glVertex3f(float(pImage->w) - image->pivotX.value, float(pImage->h) - image->pivotY.value, -image->pivotZ.value);
		dataArray[offset] = sprite->textureOffset.p - sprite->transformation.pivot.x;
		offset++;
		dataArray[offset] = sprite->textureOffset.q - sprite->transformation.pivot.y;
		offset++;
		dataArray[offset] = -sprite->transformation.pivot.z;
		offset += (20 - 2);

		//glVertex3f(-image->pivotX.value, float(pImage->h) - image->pivotY.value, -image->pivotZ.value)
		dataArray[offset] = -sprite->transformation.pivot.x;
		offset++;
		dataArray[offset] = sprite->textureOffset.q - sprite->transformation.pivot.y;
		offset++;
		dataArray[offset] = -sprite->transformation.pivot.z;
	}

	void SpriteManager::updateTexture(Sprite* sprite, GLuint offset)
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
			texturePosition.s = sprite->textureOffset.s / pageDimension.x;
			texturePosition.t = sprite->textureOffset.t / pageDimension.y;
			pageDimension.z = sprite->palettePage;
			textureDimension.z = sprite->palettePage;
		}
		else
		{
			if (sprite->animationDirection == Animation::WIDTH)
			{
				texturePosition.s = (sprite->textureOffset.s / pageDimension.x) + sprite->ptrAnimation->keyFrames[sprite->ptrAnimation->actualFrame] * textureDimension.x + sprite->ptrAnimation->keyFrames[sprite->ptrAnimation->actualFrame] * (sprite->tileSeparation.s / pageDimension.x);
				texturePosition.t = sprite->textureOffset.t / pageDimension.y;
				pageDimension.z = sprite->palettePage;
				textureDimension.z = sprite->palettePage;
			}

			if (sprite->animationDirection == Animation::HEIGHT)
			{
				texturePosition.s = sprite->textureOffset.s / pageDimension.x;
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
				pageDimension.z = sprite->ptrAnimation->keyFrames[sprite->ptrAnimation->actualFrame];
				textureDimension.z = sprite->ptrAnimation->keyFrames[sprite->ptrAnimation->actualFrame];
			}

			if (sprite->animationDirection == Animation::DEPTH_DENORMALIZED)
			{
				texturePosition.s = 0.0f;
				texturePosition.t = 0.0f;
				pageDimension.z = sprite->ptrAnimation->keyFrames[sprite->ptrAnimation->actualFrame];
				textureDimension.z = sprite->ptrAnimation->keyFrames[sprite->ptrAnimation->actualFrame];
			}

			if (sprite->animationDirection == Animation::LOOP)
			{

			}
		}

		//image->textureX.value	
		dataArray[offset] = texturePosition.s;
		offset++;
		//image->textureY.value + image->textureHeight.value	
		dataArray[offset] = texturePosition.t + textureDimension.y;
		offset++;
		dataArray[offset] = pageDimension.z;
		offset++;
		dataArray[offset] = GLfloat(sprite->texturePalette);
		offset += (20 - 3);

		//image->textureX.value + image->textureWidth.value	
		dataArray[offset] = texturePosition.s + textureDimension.x;
		offset++;
		//image->textureY.value + image->textureHeight.value);	
		dataArray[offset] = texturePosition.t + textureDimension.y;
		offset++;
		dataArray[offset] = pageDimension.z;
		offset++;
		dataArray[offset] = GLfloat(sprite->texturePalette);
		offset += (20 - 3);

		//image->textureX.value + image->textureWidth.value	
		dataArray[offset] = texturePosition.s + textureDimension.x;
		offset++;
		//image->textureY.value	
		dataArray[offset] = texturePosition.t;
		offset++;
		dataArray[offset] = pageDimension.z;
		offset++;
		dataArray[offset] = GLfloat(sprite->texturePalette);
		offset += (20 - 3);

		//image->textureX.value	
		dataArray[offset] = texturePosition.s;
		offset++;
		//image->textureY.value
		dataArray[offset] = texturePosition.t;
		offset++;
		dataArray[offset] = pageDimension.z;
		offset++;
		dataArray[offset] = GLfloat(sprite->texturePalette);
	}

	void render::SpriteManager::updateColor1(Sprite* sprite, GLuint offset)
	{
	}

	void render::SpriteManager::updateColor2(Sprite* sprite, GLuint offset)
	{
	}

	void render::SpriteManager::updateAlpha(Sprite* sprite, GLuint offset)
	{
	}

	void render::SpriteManager::updateNormal(Sprite* sprite, GLuint offset)
	{
	}

	void render::SpriteManager::updateShader(Sprite* sprite, GLuint offset)
	{
	}

	void SpriteManager::updateColor(Sprite* sprite, GLuint offset)
	{
		dataArray[offset] = sprite->vertexColor[0].r;
		offset++;
		dataArray[offset] = sprite->vertexColor[0].g;
		offset++;
		dataArray[offset] = sprite->vertexColor[0].b;
		offset++;
		dataArray[offset] = sprite->vertexColor[0].a;
		offset += (20 - 3);

		dataArray[offset] = sprite->vertexColor[1].r;
		offset++;
		dataArray[offset] = sprite->vertexColor[1].g;
		offset++;
		dataArray[offset] = sprite->vertexColor[1].b;
		offset++;
		dataArray[offset] = sprite->vertexColor[1].a;
		offset += (20 - 3);

		dataArray[offset] = sprite->vertexColor[2].r;
		offset++;
		dataArray[offset] = sprite->vertexColor[2].g;
		offset++;
		dataArray[offset] = sprite->vertexColor[2].b;
		offset++;
		dataArray[offset] = sprite->vertexColor[2].a;
		offset += (20 - 3);

		dataArray[offset] = sprite->vertexColor[3].r;
		offset++;
		dataArray[offset] = sprite->vertexColor[3].g;
		offset++;
		dataArray[offset] = sprite->vertexColor[3].b;
		offset++;
		dataArray[offset] = sprite->vertexColor[3].a;
	}

	void SpriteManager::updateTranslate(Sprite* sprite, GLuint offset)
	{
		dataArray[offset] = sprite->transformation.translate.x;
		offset++;
		dataArray[offset] = sprite->transformation.translate.y;
		offset++;
		dataArray[offset] = sprite->transformation.translate.z;
		offset += (20 - 2);

		dataArray[offset] = sprite->transformation.translate.x;
		offset++;
		dataArray[offset] = sprite->transformation.translate.y;
		offset++;
		dataArray[offset] = sprite->transformation.translate.z;
		offset += (20 - 2);

		dataArray[offset] = sprite->transformation.translate.x;
		offset++;
		dataArray[offset] = sprite->transformation.translate.y;
		offset++;
		dataArray[offset] = sprite->transformation.translate.z;
		offset += (20 - 2);

		dataArray[offset] = sprite->transformation.translate.x;
		offset++;
		dataArray[offset] = sprite->transformation.translate.y;
		offset++;
		dataArray[offset] = sprite->transformation.translate.z;
	}

	void SpriteManager::updateScale(Sprite* sprite, GLuint offset)
	{
		dataArray[offset] = sprite->transformation.scale.x;
		offset++;
		dataArray[offset] = sprite->transformation.scale.y;
		offset++;
		dataArray[offset] = sprite->transformation.scale.z;
		offset += (20 - 2);

		dataArray[offset] = sprite->transformation.scale.x;
		offset++;
		dataArray[offset] = sprite->transformation.scale.y;
		offset++;
		dataArray[offset] = sprite->transformation.scale.z;
		offset += (20 - 2);

		dataArray[offset] = sprite->transformation.scale.x;
		offset++;
		dataArray[offset] = sprite->transformation.scale.y;
		offset++;
		dataArray[offset] = sprite->transformation.scale.z;
		offset += (20 - 2);

		dataArray[offset] = sprite->transformation.scale.x;
		offset++;
		dataArray[offset] = sprite->transformation.scale.y;
		offset++;
		dataArray[offset] = sprite->transformation.scale.z;
	}

	void SpriteManager::updateRotate(Sprite* sprite, GLuint offset)
	{
		dataArray[offset] = sprite->transformation.rotate.x;
		offset++;
		dataArray[offset] = sprite->transformation.rotate.y;
		offset++;
		dataArray[offset] = sprite->transformation.rotate.z;
		offset += (20 - 2);

		dataArray[offset] = sprite->transformation.rotate.x;
		offset++;
		dataArray[offset] = sprite->transformation.rotate.y;
		offset++;
		dataArray[offset] = sprite->transformation.rotate.z;
		offset += (20 - 2);

		dataArray[offset] = sprite->transformation.rotate.x;
		offset++;
		dataArray[offset] = sprite->transformation.rotate.y;
		offset++;
		dataArray[offset] = sprite->transformation.rotate.z;
		offset += (20 - 2);

		dataArray[offset] = sprite->transformation.rotate.x;
		offset++;
		dataArray[offset] = sprite->transformation.rotate.y;
		offset++;
		dataArray[offset] = sprite->transformation.rotate.z;
	}

	void SpriteManager::batchDraw(GLenum mode)
	{
		drawingMode = mode;

		ptrVertexArray->attach();
		ptrVertexBuffer->attach();
		ptrIndexBuffer->attach();

		//Define offset to texture unit on vertex buffer
		GLuint offset = 6;

		if ((dataArray.size() / quadFloatCount) < GLuint(maxTextureUnits))
		{
			//Bind each quad texture to 32 texture units
			for (uint j = 0; j < (dataArray.size() / quadFloatCount); j++)
			{
				glActiveTexture(GL_TEXTURE0 + GLuint(dataArray[offset]));
				glBindTexture(GL_TEXTURE_2D_ARRAY, GLuint(dataArray[offset]));
				for (uint k = 0; k < 4; k++)
				{
					dataArray[offset] = GLfloat(j);
					offset += (vertexBufferStrideCount);
				}
			}
			glDrawRangeElements(drawingMode, 0, ptrIndexBuffer->bufferCount, ptrIndexBuffer->bufferCount, GL_UNSIGNED_INT, 0);
		}
		else
		{
			//Draw vertices in groups of 32
			for (uint i = 0; i < batchDrawCalls; i++)
			{
				//Bind each quad texture to 32 texture units
				for (int j = 0; j < maxTextureUnits; j++)
				{
					glActiveTexture(GL_TEXTURE0 + GLint(dataArray[offset]));
					glBindTexture(GL_TEXTURE_2D_ARRAY, GLuint(dataArray[offset]));

					for (uint k = 0; k < 4; k++)
					{
						batchDrawCount = i;
						textureCounter = j;

						dataArray[offset] = GLfloat(j);
						offset += (vertexBufferStrideCount);
					}
				}
				glDrawRangeElements(drawingMode, i * batchDrawOffset, (i * batchDrawOffset) + batchDrawOffset, ptrIndexBuffer->bufferCount, GL_UNSIGNED_INT, 0);
			}
		}
		ptrVertexArray->detach();
		ptrVertexBuffer->detach();
		ptrIndexBuffer->detach();
	}

	void SpriteManager::update()
	{
		updateEnitities();
		updateVertexBuffer();
	}

	void SpriteManager::print() const
	{
		printInfo();
		printEntities();
		printDataArray();
	}

	void SpriteManager::printInfo() const
	{
		cout << "**************************************************" << endl;
		cout << "Object Manager Info:" << endl;
		cout << "Program ID = " << programID << endl;
		cout << "Batch Draw Calls = " << batchDrawCalls << endl;
		cout << "Batch Draw Offset = " << batchDrawOffset << endl;
		cout << "Entities Buffer Size = " << entitiesArray.size() << endl;
		cout << "Data Buffer Size = " << dataArray.size() << endl;
		cout << "Quad Count = " << dataArray.size() / quadFloatCount << endl;
		cout << "Quad Float Count = " << quadFloatCount << endl;
		cout << "Vertex Buffer Stride Count = " << vertexBufferStrideCount << endl;
		cout << "**************************************************" << endl;
	}

	void SpriteManager::printDataArray() const
	{
		cout << "******************************************************************************************************************************************************************************" << endl;
		cout << "Buffer Data: " << endl;

		for (uint i = 0; i < dataArray.size(); i++)
		{
			if (i > 0)
			{
				if (i % vertexBufferStrideCount == 0)
					cout << endl;
			}
			cout << dataArray[i] << ",    ";
		}

		cout << endl << "******************************************************************************************************************************************************************************" << endl;
	}

	void SpriteManager::printEntities() const
	{
		cout << "**************************************************" << endl;
		cout << "Buffer Entities: " << endl;

		for (GLuint i = 0; i < entitiesArray.size(); i++)
			entitiesArray[i]->print();

		cout << "**************************************************" << endl;
	}
}