#pragma once
#include "Scene.h"

namespace HARIKEN {

	class Dice : public GameObject
	{
	public:

		void onCreate();

		void update();

	private:
		float angle = 0.0f;

		Collision* collider;

		glm::vec2 mousePrevPos;
		glm::vec2 mouseNowPos;

	};

}