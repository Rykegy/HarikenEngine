/*****************************************************************************
Loading scene played while the things are being loaded in the background on seperate threads.
*****************************************************************************/

#pragma once
#include "Scene.h"
#include <future>

namespace HARIKEN {

	class loadingScreen : public derivedScene<loadingScreen>
	{

	public:

		void onCreate();
		void onStart();

		void shutdown();

		std::string getName() {

			return "Loading...";

		}

		void update();

	private:

		std::vector<std::future<void>*>* loadingThreads;

	private:

		friend class SceneManager;

		void startLoading(std::vector<std::future<void>*>* loadingThreads);

		bool allThreadsDone = false;

	};

}