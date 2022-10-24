/*********************************************************************
UI Image that goes behind the text used to display dialogue and texts during battles.
*********************************************************************/

#pragma once
#include "UIObject.h"
#include "BattleScene.h"

namespace MEIUN {

	class BattleUITextbox : public HARIKEN::UIObject
	{
	public:

		void onCreate();
		void update();

	private:

		friend BattleScene;

	};

}