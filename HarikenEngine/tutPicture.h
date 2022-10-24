/**************************************************************
Used to display controls used to control overworld character during tutorial.
**************************************************************/

#pragma once
#include "GameObject.h"

namespace MEIUN {

	class tutPicture : public HARIKEN::GameObject
	{

	public:

		void onCreate();

		void update();

	};

}