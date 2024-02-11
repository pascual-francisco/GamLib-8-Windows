#include "stdafx.h"

namespace texture
{
	#ifndef TEXTUREMANAGER_H
	#define TEXTUREMANAGER_H

	class TextureManager: public Object
	{
		public:
		__declspec(dllexport) TextureManager();
		__declspec(dllexport) ~TextureManager();
		__declspec(dllexport) 	void initTexture(GLuint name, string path, GLuint quantity, GLuint target);

	};
#endif // !TEXTUREMANAGER_H
}
