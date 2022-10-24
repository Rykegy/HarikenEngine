#pragma once

#include "Scene.h"

namespace HARIKEN {

	class leveltwo : public Scene
	{
	public:
		leveltwo();
		~leveltwo();

		void onCreate();
		void onStart();

	private:

		GameObject * Test;
		GameObject * platform0;
		GameObject * platform1;
		GameObject * platform2;
		GameObject * platform4;
		GameObject * platform5;
		GameObject * platform6;
		GameObject * platform7;
		GameObject * platform8;
		GameObject * platform9;
		GameObject * platform10;
		GameObject * platform11;
		GameObject * platform12;
		GameObject * platform13;
		GameObject * platform14;
		GameObject * platform15;
		GameObject * platform16;
		GameObject * platform17;
		GameObject * platform18;
		GameObject * door;
		GameObject * coin0;
		GameObject * coin1;
		GameObject * coin2;
		GameObject * coin3;
		GameObject * coin4;
		GameObject * coin5;
		GameObject * coin6;

	};

}