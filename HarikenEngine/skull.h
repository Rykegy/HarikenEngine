#pragma once
#include "Scene.h"

namespace HARIKEN {

	class skull : public GameObject
	{
	public:

		void onCreate();

		void update();

	private:

		float angle;

	};

}