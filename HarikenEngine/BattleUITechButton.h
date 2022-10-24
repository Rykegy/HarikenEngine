/***********************************************************
UI text button that brings up a list of techniques that the player can use.
***********************************************************/

#pragma once
#include "UIObject.h"
#include "BattleScene.h"
#include "BattleUIOptionBox.h"

namespace MEIUN {

	class BattleUITechButton : public HARIKEN::UIObject
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