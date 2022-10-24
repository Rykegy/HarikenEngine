#pragma once
#include "SkyBox.h"
#include "objLoader.h"

namespace HARIKEN {

	class cnSkyBox : public SkyBox
	{
	public:

		void onCreate();
		void update();
		const void render();

	};

}