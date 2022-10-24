/************************************************
UI Text used to display exactly how much health a unit has.
************************************************/

#pragma once
#include "UIObject.h"

namespace MEIUN {

	class BattleUIHealthText : public HARIKEN::UIObject
	{
	public:

		void onCreate();
		void update();

	private:

		bool click = false;

	};


}