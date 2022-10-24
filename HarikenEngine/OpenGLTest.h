#pragma once
#include "Scene.h"

namespace HARIKEN {

	class OpenGLTest : public Scene
	{
	public:
		OpenGLTest();

		std::string getName() {

			return "OpenGL Test";

		}

		void onCreate();
		void onStart();

		GameObject* cube;

	};

}