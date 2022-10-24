/*************************************
Scene used to test collision working properly.
*************************************/

#pragma once
#include "Scene.h"
#include "TestSquare.h"
#include "TestSquareNPC.h"

namespace HARIKEN {

	class CollisionTest : public Scene
	{
	public:
		CollisionTest();
		~CollisionTest();

		void onCreate();
		void onStart();

		GameObject* Player;
		GameObject* Obstacle;

	};

}