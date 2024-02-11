#include "stdafx.h"

namespace render
{

	#ifndef RENDERER_H
	#define RENDERER_H

	class Renderer: public Object
	{
		private:	
		bool			debugMode;
		ofstream		logFile;
		string			assetsPath;
		SDL_FRect		viewPort;
		GLfloat			FPS;
		GLfloat			actualFrame;
		SDL_GLContext	ptrGLContext;
		SDL_Window*		ptrWindow;
		FrameBuffer**	ptrFrameBuffers;
		RenderBuffer**	ptrRenderBuffers;
		PixelBuffer**	ptrPixelBuffer;
		TextureManager* ptrTextureManager;
		TextureBuffer*	ptrTextureBuffer;

		vec3			zoomFactor;
		string			gameName;

		public:
		vector<Shader*> shaders;
		GLuint			actualShader;

		__declspec(dllexport)Renderer(string name = "Game", bool mode = true, string path = "Assets/Shaders/", string vs_source = "tex_rect_vert.glsl", string gs_source = "tex_rect_geom.glsl", string fs_source = "tex_rect_frag.glsl", GLfloat x = 0, GLfloat y = 0, GLfloat w = 256, GLfloat h = 224, GLfloat zoom = 3.0f);
		__declspec(dllexport)~Renderer();

		__declspec(dllexport)void	initGlobals();
		__declspec(dllexport)void	initSDL();
		__declspec(dllexport)void	initOpenGL();
		__declspec(dllexport)void	initGlew();

		__declspec(dllexport)void	init(string name = "Game", bool mode = true, string path = "Assets/Shaders/", string vs_source = "tex_rect_vert.glsl", string gs_source = "tex_rect_geom.glsl", string fs_source = "tex_rect_frag.glsl", GLfloat x = 0, GLfloat y = 0, GLfloat w = 256, GLfloat h = 224, GLfloat zoom = 3.0f);
		__declspec(dllexport)void	initShader(string vertex, string geometry, string fragment);
		__declspec(dllexport)void	activateShader(GLuint index);
		__declspec(dllexport)void	update();
		__declspec(dllexport)void	checkErrors();
	};

#endif // !RENDERER_H
}