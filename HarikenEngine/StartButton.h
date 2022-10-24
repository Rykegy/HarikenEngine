#pragma once
#include "UIObject.h"

namespace MEIUN{

	class StartButton : public HARIKEN::UIObject
	{
	public:

		void onCreate();

		void update();

	private:
		Language lang;

	};

}