
#include "stdafx.h"

Scene::Scene(GLuint id, bool act, SDL_FRect window, GLuint program)
{
	sceneID = id;
	active = act;
	programID = program;
	viewPort = window;
	projection = mat4(1.0f);
	view = mat4(1.0f);

	ptrObjects = nullptr;
	ptrBackground = nullptr;
	ptrForeground = nullptr;	
}

Scene::~Scene()
{
	delete ptrObjects;
	delete ptrBackground;
	delete ptrForeground;	
}

void Scene::update()
{
	if (ptrBackground != nullptr)
	{
		updateBackground();
		ptrBackground->update();
		ptrBackground->batchDraw();
	}

	if (ptrObjects != nullptr)
	{
		updateObjects();
		ptrObjects->update();
		ptrObjects->batchDraw();
	}

	if (ptrForeground != nullptr)
	{
		updateForeground();
		ptrForeground->update();
		ptrForeground->batchDraw();
	}
}
