/************************************************************
The UI image behind the buttons that control player action during battles. 
************************************************************/

#pragma once
#include "UIObject.h"

namespace MEIUN {

	class BattleUIActionBox : public HARIKEN::UIObject
	{
	public:

		void onCreate();
		void update();

	};

}