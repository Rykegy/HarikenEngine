#pragma once
#include "Scene.h"

namespace HARIKEN {

	class animeTestScreen : public Scene
	{
	public:

		animeTestScreen();
		~animeTestScreen();

		void onCreate();
		void onStart();

		GameObject* Anime;

	};

}