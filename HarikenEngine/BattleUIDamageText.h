/*************************************************************************
Text that appears when damage is being dealt to show the amount of damage being dealt.
*************************************************************************/

#pragma once
#include "BattleScene.h"
#include "UIObject.h"

namespace MEIUN {

	class BattleUIDamageText : public HARIKEN::UIObject
	{
	public:

		void onCreate();
		void update();

	private:

		friend BattleScene;

		bool click = false;

	};

}