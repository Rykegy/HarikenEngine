#pragma once
#include "Scene.h"

namespace HARIKEN {

	class ScottTest : public HARIKEN::derivedScene<ScottTest>
	{
	public:

		void onCreate();
		void onStart();

		std::string getName() {

			return "Scott Test";

		}

	private:

		//GameObject* skyboxObj;
		GameObject* skullObj;

	};

}