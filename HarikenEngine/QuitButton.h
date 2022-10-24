#pragma once
#include "Scene.h"

namespace MEIUN {

	class QuitButton : public HARIKEN::UIObject
	{
	public:

		void onCreate();

		void update();

	private:
		Language lang;

	};

}