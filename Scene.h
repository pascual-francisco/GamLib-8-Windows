
#include "stdafx.h"

#ifndef SCENE_H
#define	SCENE_H

class Scene
{
	public:
	bool			active;
	GLuint			sceneID;
	GLuint			programID;
	SDL_FRect		viewPort;
	mat4			projection;
	mat4			view;
	ObjectManager	*ptrObjects;
	TileMapManager	*ptrBackground;
	TileMapManager	*ptrForeground;	

	__declspec(dllexport) 	Scene(GLuint id, bool act, SDL_FRect viewport, GLuint program);
	__declspec(dllexport) virtual ~Scene();


	
	__declspec(dllexport) virtual void	initObjects()  = 0;
	__declspec(dllexport) virtual void	initBackground() = 0;
	__declspec(dllexport) virtual void	initForeground() = 0;

	__declspec(dllexport) void update();
	__declspec(dllexport) virtual void	updateObjects()  = 0;
	__declspec(dllexport) virtual void	updateBackground()  = 0;
	__declspec(dllexport) virtual void	updateForeground()  = 0;

};
#endif// !SCENE_H
