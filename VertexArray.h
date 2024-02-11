#include "stdafx.h"

namespace render
{
	#ifndef VERTEXARRAY_H
	#define	VERTEXARRAY_H

	class VertexArray: public Object
	{
		public:
		__declspec(dllexport) VertexArray();
		__declspec(dllexport) ~VertexArray();

		__declspec(dllexport) void init();
		__declspec(dllexport) void attach() const;
		__declspec(dllexport) void detach() const;
	};
	#endif // !VERTEXBUFFER_H
}