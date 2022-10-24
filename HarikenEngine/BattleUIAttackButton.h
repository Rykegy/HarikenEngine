/********************************************************
Text button that makes the player character perform a normal attack.
********************************************************/

#pragma once
#include "UIObject.h"
#include "BattleScene.h"

namespace MEIUN {

	class BattleUIAttackButton : public HARIKEN::UIObject
	{
	public:

		void onCreate();
		void update();

	private:

		friend BattleScene;

		bool click = false;

	};

}