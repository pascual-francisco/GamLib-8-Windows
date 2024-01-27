#include "stdafx.h"

#ifndef SPRITE_H
#define SPRITE_H

class Sprite
{
	public:
	GLuint			spriteID;
	bool 			active;
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
	vec4			secondaryColor[4];		
	vec4			vertexColor[4];

	__declspec(dllexport) Sprite(GLuint spriteID = 0, GLuint pte = 0, GLuint pge = 0, GLfloat s = 0.0f, GLfloat t = 0.0f, GLfloat p = 1.0f, GLfloat q = 1.0f, GLfloat tix = 0.0f, GLfloat tiy = 0.0f, GLuint tsx = 0, GLuint tsy = 0, GLuint cda = 0, GLuint adi = 0, GLint fie = 0, GLint lae = 0, GLint ace = 0, GLfloat frt = 0, GLuint ste = Animation::STOP);
	__declspec(dllexport) Sprite(const Sprite &);
	__declspec(dllexport) ~Sprite();

	__declspec(dllexport) void init(GLuint spriteID = 0, GLuint pte = 0, GLuint pge = 0, GLfloat s = 0.0f, GLfloat t = 0.0f, GLfloat p = 1.0f, GLfloat q = 1.0f, GLfloat tix = 0.0f, GLfloat tiy = 0.0f, GLuint tsx = 0, GLuint tsy = 0, GLuint cda = 0, GLuint adi = 0, GLint fie = 0, GLint lae = 0, GLint ace = 0, GLfloat frt = 0, GLuint ste = Animation::STOP);
	__declspec(dllexport) const Sprite &operator=(const Sprite &);
	__declspec(dllexport) bool operator==(const Sprite &) const;
	__declspec(dllexport) bool operator<(const Sprite &) const;
	__declspec(dllexport) bool operator>(const Sprite &) const;
	__declspec(dllexport) bool operator*( Sprite &) ;
	__declspec(dllexport) void update();
	__declspec(dllexport) void print() const;
};

#endif // !SPRITE_H

