/***********************************************
UI Text used to display exactly how much mana a unit has.
***********************************************/

#pragma once
#include "UIObject.h"

namespace MEIUN {

	class BattleUIManaText : public HARIKEN::UIObject
	{
	public:

		void onCreate();
		void update();

	private:

		bool click = false;

	};

}