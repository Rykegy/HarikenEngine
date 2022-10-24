#include "stdafx.h"
#include "WindowSys.h"
#include <glew.h>

using namespace HARIKEN;

std::unique_ptr<WindowSys> WindowSys::instance = nullptr;

WindowSys::WindowSys()
{
}


WindowSys::~WindowSys()
{
}

WindowSys * HARIKEN::WindowSys::GetInstance()
{

	if (instance.get() == nullptr)
		instance.reset(new WindowSys);

	return instance.get();

}

bool WindowSys::init() {

	size.x = 1280;
	size.y = 720;

	winScale = size.x / 1280.0f;
	windowScale = &winScale;

	posScale = winScale * 80.0f;
	positionScale = &posScale;

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);/// Enable Depth Cueing (the Z-buffer) 
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);/// Turn on double buffering with a 24bit Z buffer. 
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	
	window = SDL_CreateWindow("!!!HARIKEN!!!",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		size.x, size.y, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	if (window == NULL) {
		fprintf(stderr, "Window could not be created: %s\n", SDL_GetError());
		KMS = true;
		return false;
	}

	SDL_GetWindowWMInfo(window, &windowInfo);
	SDL_VERSION(&windowInfo.version);
	
	glContext = SDL_GL_CreateContext(window);
	if (glContext == nullptr) {
		printf("Cannot create OpenGL Context");
		return false;
	}
	
	primaryContext = wglGetCurrentContext();

	wglMakeCurrent(getHDC(), primaryContext);

	/// Fire up the GL Extension Wrangler
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK) {
		assert(0);
	}
	
	if (SDL_GL_SetSwapInterval(1) < 0) {
		printf("REEE");
	}

	glViewport(0, 0, size.x, size.y);

	sceneManager = SceneManager::GetInstance();

	return true;

}

void WindowSys::update(float deltaTime)
{

	

}
#include "SceneManager.h"
void WindowSys::render() {

	Scene* currentScene = sceneManager->currentScene;
	if (currentScene->KMS)
		return;

	std::string windowname = "Hariken Engine - " + currentScene->getName();

	const char* title = { windowname.c_str()	};

	SDL_SetWindowTitle(window, title);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(currentScene->bgColor.r, currentScene->bgColor.g, currentScene->bgColor.b, 1.0f);
	if (currentScene->twoD) {
		glDisable(GL_DEPTH_TEST);
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//SDL_RenderClear(screenRender);
	//SDL_SetRenderDrawColor(screenRender, 255, 255, 255, 255);
	currentScene->render();
	SDL_GL_SwapWindow(window);
	//SDL_RenderPresent(screenRender);

}

bool WindowSys::shutdown()
{
	
	if (KMS)
		return true;

	return false;

}

glm::vec2 HARIKEN::WindowSys::getWinSize()
{

	return size;

}

const HWND HARIKEN::WindowSys::getHWND()
{
	return windowInfo.info.win.window;
}

const HDC HARIKEN::WindowSys::getHDC()
{
	return GetDC(getHWND());
}

HGLRC HARIKEN::WindowSys::getPrimaryContext()
{
	return primaryContext;
}

HGLRC HARIKEN::WindowSys::newThreadContext()
{

	HGLRC secondaryContext = wglCreateContext(getHDC());

	wglShareLists(primaryContext, secondaryContext);

	return secondaryContext;

}
