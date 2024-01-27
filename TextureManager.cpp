#include "stdafx.h"

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{

}

void TextureManager::initTexture(GLuint name, string path, GLuint quantity, GLuint target)
{
	GLuint textureID = 0;	
	string file;
	SDL_Surface *ptrImage = NULL;

	glGenTextures(1, &textureID);
	glBindTexture(target, textureID);

	glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	if (target == GL_TEXTURE_2D_ARRAY)
	{
		if (quantity == 1)
		{
			file = path + ".png";
			ptrImage = IMG_Load(file.c_str());
			
			if (ptrImage != NULL)
				glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, ptrImage->w, ptrImage->h, quantity, 0, GL_RGBA, GL_UNSIGNED_BYTE, ptrImage->pixels);
		}
		else
		{
			file = path + "_0000" + ".png";

			ptrImage = IMG_Load(file.c_str());

			if (ptrImage != NULL)
				glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, ptrImage->w, ptrImage->h, quantity, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

			for (GLuint i = 0; i < quantity; i++)
			{
				if (i < 10)
					file = path + "_000" + to_string(i) + ".png";

				if (i >= 10 && i < 100)
					file = path + "_00" + to_string(i) + ".png";

				if (i > 100 && i < 1000)
					file = path + "_0" + to_string(i) + ".png";

				ptrImage = IMG_Load(file.c_str());

				if (ptrImage != NULL)
					glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, ptrImage->w, ptrImage->h, 1, GL_RGBA, GL_UNSIGNED_BYTE, ptrImage->pixels);
			}
		}
	}		
	SDL_FreeSurface(ptrImage);	
}