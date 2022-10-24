/*********************************************************************
Empty UI text designed to hold battle dialogue and texts displayed during the battle.
*********************************************************************/

#pragma once
#include "UIObject.h"
#include "BattleScene.h"

namespace MEIUN {

	class BattleUIText : public HARIKEN::UIObject
	{
	public:

		void onCreate();
		void update();

	private:

		friend BattleScene;

	};

}