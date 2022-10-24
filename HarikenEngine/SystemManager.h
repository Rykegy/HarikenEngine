#pragma once
#include "WindowSys.h"
#include "InputSys.h"
#include "Scene.h"
#include <vector>
#include "vec.h"

namespace HARIKEN {

	class SystemManager
	{

	public:
		SystemManager();
		~SystemManager();

		bool init();
		void update(float deltaTime);
		const void render(Scene* currentScene);
		bool shutdown();

		input getInput();
		vec getWindowSize();

	protected:

		WindowSys * windowsys;
		InputSys* inputsys;

	};

}