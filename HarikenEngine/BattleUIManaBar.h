/***************************************************
UI Image used to visually display how much a mana a unit has.
***************************************************/

#pragma once
#include "UIObject.h"

namespace MEIUN {

	class BattleUIManaBar : public HARIKEN::UIObject
	{
	public:

		void onCreate();
		void update();

		void setInitialMana(float MP);
		void subtractMana(float cost);

	private:

		bool click = false;

		float initialMana;
		float currentMana;
		float newMana;
		float deductionRate;

	};

}