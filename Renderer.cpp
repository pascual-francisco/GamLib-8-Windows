#include "stdafx.h"

Renderer::Renderer(string name, bool mode, string path, string vs_source, string gs_source, string fs_source, GLfloat x, GLfloat y, GLfloat w, GLfloat h, GLfloat zoom)
{	
	ptrWindow = nullptr;
	ptrFrameBuffers = nullptr;
	ptrRenderBuffers = nullptr;
	ptrPixelBuffer = nullptr;
	ptrTextureManager = nullptr;
	ptrTextureBuffer = nullptr;
	init( name, mode, path, vs_source, gs_source, fs_source, x, y, w, h, zoom);	
}

Renderer::~Renderer()
{
	delete[] ptrFrameBuffers;
	delete[] ptrRenderBuffers;
	delete ptrTextureManager;
	delete ptrTextureBuffer;
	delete ptrPixelBuffer;
	logFile.close();
}


void Renderer::init(string name, bool mode, string path, string vs_source, string gs_source, string fs_source, GLfloat x, GLfloat y, GLfloat w, GLfloat h, GLfloat zoom)
{
	debugMode = mode;
	active = true;

	FPS = 60.0;
	actualFrame = 0;
	viewPort.x = x;
	viewPort.y = y;
	viewPort.w = w;
	viewPort.h = h;
	assetsPath = path;
	zoomFactor.x = zoom;
	zoomFactor.y = zoom;
	zoomFactor.z = zoom;
	actualShader = 0;
	gameName = name;

	initGlobals();
	initSDL();
	initOpenGL();
	initGlew();
	initShader(vs_source, gs_source, fs_source);

	if (shaders[actualShader] != nullptr)
		shaders[actualShader]->attach();
}

void Renderer::initGlobals()
{

}

void Renderer::initSDL()
{
	if (!logFile.is_open())
	{
		logFile.open(assetsPath + "Rendererlog.txt", ios::trunc);
	}

	int sdlResult = 0;
	char buffer[300] = {0};

	time_t now = time(0);
		
	ctime_s(buffer, 300, &now);
	
	logFile << "-------------------------------------------------------------------------------------------------------------------------------------";
	logFile << endl << "Renderer Log: " << buffer;

	//Initalize SDL//
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		logFile << "SDL Error: Initialization SDL Error" << SDL_GetError() << endl;
		cout << "SDL Error: Initialization SDL Error" << endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		logFile << "SDL initialized no error" << endl;
		cout << "SDL initialized no error" << endl;
	}

	//Initalize SDL_IMAGE//
	if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF ))
	{
		cout << "SDL_Image Error: Initialization SDL_Image Error" << SDL_GetError() << endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		logFile << "SDL_Image initialized no error" << endl;
		cout << "SDL_Image initialized no error" << endl;
	}

	//Create window//
	ptrWindow = SDL_CreateWindow(gameName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, viewPort.w * zoomFactor.x, viewPort.h * zoomFactor.y, SDL_WINDOW_OPENGL);
	if (ptrWindow == NULL)
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		logFile << "Window could not be created! SDL Error: %s\n", SDL_GetError();
	}
	else
	{
		//Create context//
		if (ptrGLContext = SDL_GL_CreateContext(ptrWindow))
		{
			cout << "OpenGL context created no error" << endl;
			logFile << "OpenGL context created no error" << endl;
		}

		if (ptrGLContext == NULL)
		{
			printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
			logFile << "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError();
		}
		else
		{
			//Use Vsync//
			if (SDL_GL_SetSwapInterval(1) < 0)
			{
				printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
				logFile << "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError();
			}
		}
	}
}

void Renderer::initOpenGL()
{
	//Initalize OpenGL//
	GLenum glewError = 0;
	char buffer[300] = { 0 };
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH, GL_NICEST);

	logFile << "OpenGL initialized version: " << glGetString(GL_VERSION) << endl;
	if (glGetError() == GL_NO_ERROR)
	{
		logFile << "OpenGL initialized no error" << endl;
	}

	glViewport(0, 0, viewPort.w * zoomFactor.x, viewPort.h * zoomFactor.y);

	if (debugMode)
	{
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	}
	else
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	}
}

void Renderer::initGlew()
{
	GLenum glewError = 0;

	//Initalize GLEW//
	glewError = glewInit();

	//GLEW Ok
	if (glewError == GLEW_OK)
	{
		logFile << "GLEW initialized no error" << endl;
		cout << "GLEW initialized no error" << endl;
	}

	//Missing GL version
	if (glewError == GLEW_ERROR_NO_GL_VERSION)
	{
		logFile << "GLEW Error: Missing GL version" << endl;
		cout << "GLEW Error: Missing GL version" << endl;
		exit(EXIT_FAILURE);
	}

	//Need at least OpenGL 1.1
	if (glewError == GLEW_ERROR_GL_VERSION_10_ONLY)
	{
		logFile << "GLEW Error: Need at least OpenGL 1.1" << endl;
		cout << "GLEW Error: Missing GL version" << endl;
		exit(EXIT_FAILURE);
	}

	if (glewError == GLEW_ERROR_GLX_VERSION_11_ONLY)
	{
		logFile << "GLEW Error: Need at least GLX 1.2" << endl;
		cout << "GLEW Error: Need at least GLX 1.2" << endl;
		exit(EXIT_FAILURE);
	}

	if (glewError == GLEW_ERROR_NO_GLX_DISPLAY)
	{
		logFile << "GLEW Error: Need GLX display for GLX support" << endl;
		cout << "GLEW Error: Need GLX display for GLX support" << endl;
		exit(EXIT_FAILURE);
	}
}

void Renderer::initShader(string vertex, string geometry, string fragment)
{
	//Initialize all the program shaders//
	shaders.push_back(new Shader(assetsPath, vertex, geometry, fragment));
}

void Renderer::activateShader(GLuint id)
{
	if (id >= 0 && id < shaders.size() - 1)
	{
		if (id != actualShader)
		{
			shaders[actualShader]->detach();
			actualShader = id;
			shaders[actualShader]->attach();
		}
	}
}

void Renderer::update()
{
	//checkErrors();
	SDL_GL_SwapWindow(ptrWindow);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_ACCUM_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Renderer::checkErrors()
{
	//Check OpenGL Errors//
	GLenum error = 0;
	error = glGetError();

	if (error == GL_INVALID_ENUM)
	{
		logFile << "OpenGL Error: GL_INVALID_ENUM An unacceptable value is specified for an enumerated argument." << endl;
		cout << "OpenGL Error: GL_INVALID_ENUM An unacceptable value is specified for an enumerated argument." << endl;
		exit(EXIT_FAILURE);
	}

	if (error == GL_INVALID_VALUE)
	{
		logFile << "OpenGL Error: GL_INVALID_VALUE A numeric argument is out of range." << endl;
		cout << "OpenGL Error: GL_INVALID_VALUE A numeric argument is out of range." << endl;
		exit(EXIT_FAILURE);
	}

	if (error == GL_INVALID_OPERATION)
	{
		logFile << "OpenGL Error: GL_INVALID_OPERATION The specified operation is not allowed in the current state." << endl;
		cout << "OpenGL Error: GL_INVALID_OPERATION The specified operation is not allowed in the current state." << endl;
		exit(EXIT_FAILURE);
	}

	if (error == GL_INVALID_FRAMEBUFFER_OPERATION)
	{
		logFile << "OpenGL Error: GL_INVALID_FRAMEBUFFER_OPERATION The command is trying to Renderer to or read from the framebuffer while the currently bound framebuffer is not framebuffer complete." << endl;
		cout << "OpenGL Error: GL_INVALID_FRAMEBUFFER_OPERATION The command is trying to Renderer to or read from the framebuffer while the currently bound framebuffer is not framebuffer complete." << endl;
		exit(EXIT_FAILURE);
	}

	if (error == GL_OUT_OF_MEMORY)
	{
		logFile << "OpenGL Error: GL_OUT_OF_MEMORY There is not enough memory left to execute the command. " << endl;
		cout << "OpenGL Error: GL_OUT_OF_MEMORY There is not enough memory left to execute the command. " << endl;
		exit(EXIT_FAILURE);
	}
}