#include "stdafx.h"
#include "Engine.h"

using namespace HARIKEN;

std::unique_ptr<Engine> Engine::engine(nullptr);

Engine::Engine()
{
}

Engine::~Engine()
{
	IMG_Quit();
	SDL_QUIT;
	isRunning = false;
}

void HARIKEN::Engine::readConfig()
{

	FILE* fptr;

	errno_t err;

	err = fopen_s(&fptr, "config", "rb");
	if (err == 0)
	{
		fread_s(&language, sizeof(language), 1, 1, fptr);
	}
	else
	{
		fopen_s(&fptr, "config", "wb");
		fwrite(&language, sizeof(Language), 1, fptr);
	}

	fclose(fptr);

}

Engine * Engine::startEngine()
{
	engine.reset(new Engine);
	return engine.get();
}

int Engine::init() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "SDL video init failed: %s\n", SDL_GetError());
		return 1;
	}

	time = Time::GetInstance();

	isRunning = true;
	framerate = 60;

	windowSys = WindowSys::GetInstance();
	windowSys->init();

	inputSys = InputSys::GetInstance();
	inputSys->init();

	Camera::GetInstance()->addLightSource(new LightSource(glm::vec3(0.0f, 0.0f, 2.0f), 0.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f)));

	AssetHandler::GetInstance();

	GlobalObjectsHandler::GetInstance();
	ShaderHandler::GetInstance();
	Animation2DHandler::GetInstance();

	readConfig();

	sceneMgr = SceneManager::GetInstance();
	sceneMgr->init();

	return 0;

}

int Engine::Run()
{

	while (isRunning) {

		time->update();

		inputSys->update();
		sceneMgr->update();

		if (inputSys->shutdown() || sceneMgr->shutdown() || windowSys->shutdown()) {

			IMG_Quit();
			SDL_QUIT;
			isRunning = false;
			break;

		}
			
		windowSys->render();

	}

	return 0;

}
