#include "Game.h"
 
Game::Game(string name, bool mode, string file, string vs_source, string gs_source, string fs_source, GLfloat x, GLfloat y, GLfloat w, GLfloat h, GLfloat zoom)
{
	assetsPath = file;
	viewPort.x = x;
	viewPort.y = y;
	viewPort.w = w;
	viewPort.h = h;
	actualScene = 0;
	active = true;
	debugMode = mode;
	ptrRenderer = nullptr;
	ptrJoystick = nullptr;
	ptrRenderer = new Renderer(name, mode, file, vs_source, gs_source, fs_source, x, y, w, h, zoom);
}

Game::~Game()
{
	delete ptrRenderer;
	delete ptrTextureManager;
	delete ptrCamera;
}
