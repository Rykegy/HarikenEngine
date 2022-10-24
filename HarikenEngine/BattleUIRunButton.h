/*********************************************************
UI text button that allows the player to run from an enemy encounter.
*********************************************************/

#pragma once
#include "BattleScene.h"
#include "UIObject.h"

namespace MEIUN {

	class BattleUIRunButton : public HARIKEN::UIObject
	{
	public:

		void onCreate();
		void update();

	private:

		friend BattleScene;

		bool click = false;

	};

}