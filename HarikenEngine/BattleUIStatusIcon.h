/*****************************************************************************
Empty UI image used to hold a miniature version of the unit icon to be placed in the status bar.
*****************************************************************************/

#pragma once
#include "UIObject.h"
#include "BattleScene.h"

namespace MEIUN {

	class BattleUIStatusIcon : public HARIKEN::UIObject
	{
	public:

		void onCreate();
		void update();

	private:

		friend BattleScene;

		void setUnitIcon(const HARIKEN::Texture* unitIconTextureID);

	};

}