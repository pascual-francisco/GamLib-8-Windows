#pragma once

//Standard Libraries//
#include "framework.h"
#include <windows.h>
#include <unordered_map>
#include <map>
#include <stack>
#include <vector>
#include <math.h>
#include <cstring>
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <typeinfo>
#include <time.h>
#include <profileapi.h>

using namespace std;

//Libraries//
#include <glew.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
using namespace glm;

#include "Object.h"
using namespace object;

#include "TimerDelegate.h"
#include "Timer.h"

#include "TrackAction.h"
#include "KeyFrameDelegate.h"
#include "KeyFrame.h"
#include "TrackDelegate.h"
#include "Track.h"
#include "Animation.h"
#include "AnimationDelegate.h"

#include "EntityDelegate.h"
#include "SpriteDelegate.h"
//#include "SoundDelegate.h"

#include "TextureManager.h"
#include "Transformation.h"
#include "Mechanics.h"
#include "FSMState.h"
#include "Sprite.h"
#include "Entity.h"

#include "BufferObject.h"
#include "RenderBuffer.h"
#include "PixelBuffer.h"
#include "PackBuffer.h"
#include "UnpackBuffer.h"
#include "FeedbackBuffer.h"
#include "TextureBuffer.h"
#include "FrameBuffer.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "UniformBuffer.h"
#include "IndexBuffer.h"
#include "TileMapManager.h"
#include "SpriteManager.h"
#include "Camera.h"
#include "Scene.h"
#include "Renderer.h"
#include "Game.h"


using namespace physic;
using namespace animation;
using namespace object;
using namespace render;
using namespace buffer;