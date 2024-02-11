#include "stdafx.h"

namespace physic
{
	#ifndef TRANSFORMATION_H
	#define TRANSFORMATION_H

	class Transformation: public Object
	{
		public:
		vec3	translate;
		vec3	rotate;
		vec3	scale;
		vec3	pivot;

		__declspec(dllexport)	Transformation();		
		__declspec(dllexport)	~Transformation();

		__declspec(dllexport) void	init();
		__declspec(dllexport) void print() const;
		__declspec(dllexport) void update();
	};
	#endif
}


