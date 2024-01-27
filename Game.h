#include "stdafx.h"

#ifndef GAME_H
#define GAME_H

class Game
{
	public:		
	GLuint		   	actualScene;
	string			assetsPath;
	SDL_FRect		viewPort;
	bool			active;
	bool			debugMode;
	
	SDL_Event		gameEvents;
	GLuint			joystickCount;	
	Renderer		*ptrRenderer;
	TextureManager	*ptrTextureManager;	
	vector<Scene *> scenes;
	Camera			*ptrCamera;
	SDL_Joystick    *ptrJoystick;

	__declspec(dllexport) Game(string name, bool mode, string file, string vs_source, string gs_source, string fs_source, GLfloat x, GLfloat y, GLfloat w, GLfloat h, GLfloat zoom);
	__declspec(dllexport) ~Game();
	
	__declspec(dllexport) virtual void	initScenes() = 0;
	__declspec(dllexport) virtual void	initTextures() = 0;
	__declspec(dllexport) virtual void	initSounds() = 0;
	__declspec(dllexport) virtual void	initUniforms() = 0;
	__declspec(dllexport) virtual void	initBuffers() = 0;

	__declspec(dllexport) virtual void	update() = 0;
	__declspec(dllexport) virtual void	updateUniforms() = 0;
	__declspec(dllexport) virtual void	updateTextures() = 0;
	__declspec(dllexport) virtual void	updateSounds() = 0;
	__declspec(dllexport) virtual void	updateBuffers() = 0;
	__declspec(dllexport) virtual void	updateScene() = 0;
	__declspec(dllexport) virtual void	checkEvents() = 0;

	
};

#endif // !GAME_H

