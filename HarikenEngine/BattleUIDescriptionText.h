/******************************************************************************
Empty UI Text used to hold text that describes the functions of the highlighted skill or technique.
******************************************************************************/

#pragma once
#include "UIObject.h"
#include "BattleScene.h"

namespace MEIUN {

	class BattleUIDescriptionText : public HARIKEN::UIObject
	{
	public:

		void onCreate();
		void update();

	private:

		friend BattleScene;

	};

}