/*************************************
Used to initiate and start running the engine.
*************************************/

#pragma once
#include "RKGBinary.h"
#include <memory>
#include <SDL.h>
#include <SDL_image.h>
#include "WindowSys.h"
#include "InputSys.h"
#include "SceneManager.h"
#include "Time.h"
#include "ShaderHandler.h"

namespace HARIKEN {

	class Engine
	{
	public:

		static Engine* startEngine();

		int init();
		int Run();

	protected:

		Engine();
		~Engine();

		static std::unique_ptr<Engine>engine;
		friend std::default_delete<Engine>;

		bool isRunning = false;

		int framerate;

	protected:

		Time* time;
		WindowSys* windowSys;
		InputSys* inputSys;
		SceneManager* sceneMgr;

		void readConfig();

	};

}