#pragma once
#include "Scene.h"

namespace HARIKEN {

	class levelone : public Scene
	{
	public:
		levelone();
		~levelone();

		void onCreate();
		void onStart();

	private:

		GameObject * Test;
		GameObject * platform0;
		GameObject * platform1;
		GameObject * door;
		GameObject * coin0;
		GameObject * coin1;
		GameObject * coin2;
		GameObject * respawn;

	};

}