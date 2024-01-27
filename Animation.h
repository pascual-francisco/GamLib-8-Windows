#include "stdafx.h"

#ifndef ANIMATION_H
#define ANIMATION_H

class Animation
{
    public:
	GLuint		animationState;
	GLint		firstFrame;
	GLint		lastFrame;
	GLint		actualFrame;
	GLfloat		frameCounter;
	GLfloat		frameTime;
	GLuint		loopCounter;
	vector<GLint>	keyFrames;
	bool		loop;

	enum AnimationStates
	{
		FORWARD = 0,
		BACKWARD,
		LOOP_FORWARD,
		LOOP_BACKWARD,
		FORWARD_BACKWARD,
		PAUSE,
		STOP
	};

	enum AnimationDirection
	{
		S = 0, WIDTH = 0,
		T = 1, HEIGHT = 1,
		PN = 2, DEPTH_NORMALIZED = 2,
		PD = 3, DEPTH_DENORMALIZED = 3,
		ST = 4, LOOP = 4
	};

	__declspec(dllexport) Animation(GLint firstframe = 0, GLint lastframe = 1, GLint actualframe = 0, GLfloat frametime = 0, GLuint actualstate = 0);
	__declspec(dllexport) Animation(const Animation &);
	__declspec(dllexport) ~Animation();

	__declspec(dllexport) void init(GLint firstframe = 0, GLint lastfframe = 1, GLint actualframe = 0, GLfloat frametime = 0, GLuint actualstate = 0);
	__declspec(dllexport) void update();
	__declspec(dllexport) void print() const;

	__declspec(dllexport) const Animation &operator=(const Animation &);
	__declspec(dllexport) bool operator==(const Animation &) const;
	__declspec(dllexport) bool operator<(const Animation &) const;
	__declspec(dllexport) bool operator>(const Animation &) const;
	__declspec(dllexport) bool operator*( Animation &) ;
 };

#endif // ANIMATION_H

