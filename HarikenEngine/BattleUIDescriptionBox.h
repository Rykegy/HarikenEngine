/***********************************************************************************
The UI image layered behind the text shown to describe the function of a particular skill or technique.
***********************************************************************************/

#pragma once
#include "BattleScene.h"
#include "UIObject.h"

namespace MEIUN {

	class BattleUIDescriptionBox : public HARIKEN::UIObject
	{
	public:

		void onCreate();
		void update();

	private:

		friend BattleScene;

	};

}