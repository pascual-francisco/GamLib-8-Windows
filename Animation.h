#pragma once
#include "stdafx.h"

namespace animation
{
	#ifndef ANIMATION_H
	#define ANIMATION_H

	class Animation: public Object
	{
		public:
		GLuint			animationState;
		GLint			firstFrame;
		GLint			lastFrame;
		GLint			actualFrame;
		GLfloat			frameCounter;
		GLfloat			frameTime;
		GLuint			loopCounter;
		vector<GLuint>	keyFrames;		
		bool			loop;

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

		__declspec(dllexport) Animation();
		__declspec(dllexport) Animation(GLint firstframe = 0, GLint lastframe = 1, GLint actualframe = 0, GLfloat frametime = 0, GLuint actualstate = 0);
		__declspec(dllexport) Animation(const Animation&);
		__declspec(dllexport) ~Animation();

		__declspec(dllexport) void init(GLint firstframe = 0, GLint lastfframe = 1, GLint actualframe = 0, GLfloat frametime = 0, GLuint actualstate = 0);
		__declspec(dllexport) void update();
		__declspec(dllexport) void print() const;

		__declspec(dllexport) const Animation& operator=(const Animation& obj);
		__declspec(dllexport) bool operator==(const Animation& obj) const;
		__declspec(dllexport) bool operator<(const Animation& obj) const;
		__declspec(dllexport) bool operator<(uint n) const;
		__declspec(dllexport) bool operator>(const Animation& obj) const;
		__declspec(dllexport) bool operator>(uint n) const;
		__declspec(dllexport) Animation& operator-(const Animation& obj) const;
		__declspec(dllexport) void operator-(uint n);
		__declspec(dllexport) void operator--();
		__declspec(dllexport) Animation& operator+(const Animation& obj) const;
		__declspec(dllexport) void operator+(uint n);
		__declspec(dllexport) void operator++();						
		__declspec(dllexport) void operator>>(uint n);		
		__declspec(dllexport) void operator<<(uint n);
		__declspec(dllexport) Animation& operator[](uint i) const;		
		__declspec(dllexport) int operator[](int i) const;
		__declspec(dllexport) Animation& operator()(void* fun_ptr, uint x) const;
		__declspec(dllexport) Animation& operator()(uint x, uint y, uint z) const;
	};	
	#endif // ANIMATION_H
}
