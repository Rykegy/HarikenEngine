/**************************************************
UI image used to visually display how much health a unit has.
**************************************************/

#pragma once
#include "UIObject.h"

namespace MEIUN {

	class BattleUIHealthBar : public HARIKEN::UIObject
	{
	public:

		void onCreate();
		void update();

		void setInitialHealth(float HP);
		void subtractHealth(float damage);

	private:

		bool click = false;

		float initialHealth;
		float currentHealth;
		float newHealth;
		float deductionRate;

	};

}