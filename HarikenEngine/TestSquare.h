#pragma once
#include "Scene.h"

namespace HARIKEN {

	class TestSquare : public GameObject
	{
	public:

		void onCreate();

		void update();

	private:

		float speed = 5;
		Collision * collider;
		bool jumpHeld;

	};

}