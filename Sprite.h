#include "stdafx.h"

namespace render
{
	#ifndef SPRITE_H
	#define SPRITE_H

	class Sprite: public Object
	{
		public:				
		GLuint 			texturePalette;
		GLuint 			palettePage;
		vec4			textureOffset;
		vec2			tileIndex;
		Transformation	transformation;
		vec2			positionOffset;
		GLuint			collisionData;
		Animation*		ptrAnimation;
		GLuint			animationDirection;
		vec2			tileSeparation;
		vec4			alphaColor[4];
		vec4			secondaryColor[4];
		vec4			vertexColor[4];
		vec4			shader[4];
		vec4			normal[4];
		
		__declspec(dllexport) Sprite();
		__declspec(dllexport) Sprite(GLuint spriteID = 0, GLuint palette = 0, GLuint page = 0, GLfloat s = 0.0f, GLfloat t = 0.0f, GLfloat p = 1.0f, GLfloat q = 1.0f, GLfloat tilex = 0.0f, GLfloat tiley = 0.0f, GLuint tilesx = 0, GLuint tilesy = 0, GLuint collision = 0, GLuint animationdir = 0, GLint firstframe = 0, GLint lastframe = 0, GLint actualframe = 0, GLfloat frametime = 0, GLuint actualstate = Animation::STOP);
		__declspec(dllexport) Sprite(const Sprite&);
		__declspec(dllexport) ~Sprite();

		__declspec(dllexport) void init(GLuint spriteID = 0, GLuint palette = 0, GLuint page = 0, GLfloat s = 0.0f, GLfloat t = 0.0f, GLfloat p = 1.0f, GLfloat q = 1.0f, GLfloat tilex = 0.0f, GLfloat tiley = 0.0f, GLuint tilesx = 0, GLuint tilesy = 0, GLuint collision = 0, GLuint animationdir = 0, GLint firstframe = 0, GLint lastframe = 0, GLint actualframe = 0, GLfloat frametime = 0, GLuint actualstate = Animation::STOP);
		__declspec(dllexport) const Sprite& operator=(const Sprite&);
		__declspec(dllexport) bool operator==(const Sprite&) const;
		__declspec(dllexport) bool operator<(const Sprite&) const;
		__declspec(dllexport) bool operator>(const Sprite&) const;
		__declspec(dllexport) bool operator*(Sprite&);
		__declspec(dllexport) void update();
		__declspec(dllexport) void print() const;
	};
	#endif // !SPRITE_H
}
