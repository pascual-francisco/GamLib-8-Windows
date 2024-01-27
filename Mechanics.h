
#include "stdafx.h"

#ifndef MECHANICS_H
#define	MECHANICS_H

class Mechanics
{
	public:
	vec3	direction;
	vec3	position;
	vec3	speed;
	vec3	maxSpeed;
	vec3	acceleration;
	
	GLfloat	mass;
	vec3	momentum;
	vec3	inertia;
	vec3	friction;
	vec3	gravity;

	__declspec(dllexport) Mechanics();
	__declspec(dllexport) Mechanics(const Mechanics &);
	__declspec(dllexport) ~Mechanics();

	__declspec(dllexport) const Mechanics &operator=(const Mechanics &);
	__declspec(dllexport) bool operator==(const Mechanics &) const;
	__declspec(dllexport) bool operator<(const Mechanics &) const;
	__declspec(dllexport) bool operator>(const Mechanics &) const;
	__declspec(dllexport) bool operator*(const Mechanics &) const;	
	__declspec(dllexport) void update();
	__declspec(dllexport) void print() const;
};

#endif // !MECHANICS_H
