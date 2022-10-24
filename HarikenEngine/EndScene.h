#pragma once

#include "Scene.h"

namespace HARIKEN {

	class EndScene : public Scene
	{
	public:
		EndScene();
		~EndScene();

		void onCreate();
		void onStart();

	};

}