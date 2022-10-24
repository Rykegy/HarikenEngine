#pragma once
#include "Scene.h"

namespace HARIKEN {

	class Apple : public GameObject
	{
	public:

		void onCreate();

		void update();

	private:
		float angle = 0.0f;
		Collision* collider;

	};

}

