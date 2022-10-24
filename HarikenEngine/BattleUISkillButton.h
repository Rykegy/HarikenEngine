/******************************************************
UI text button that brings up a list of skills that the player can use.
******************************************************/

#pragma once
#include "BattleScene.h"
#include "UIObject.h"
#include "BattleUIOptionBox.h"

namespace MEIUN {

	class BattleUISkillButton : public HARIKEN::UIObject
	{
	public:

		void onCreate();
		void update();

	private:

		friend BattleScene;

		bool click = false;

		BattleUIOptionBox* opBox;

	};

}