
#include "stdafx.h"

#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

class Transformation
{
public:
	vec3	translate;
	vec3	rotate;
	vec3	scale;
	vec3	pivot;

	__declspec(dllexport)  Transformation();
	__declspec(dllexport) void init();
	__declspec(dllexport) ~Transformation();

	__declspec(dllexport) void print() const;
};
#endif


