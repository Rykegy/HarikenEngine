/********************************************************************
An empty UI Image slot designed to hold the character icon of a unit during its turn.
*****************************************************************#**/

#pragma once

#include "UIObject.h"
#include "BattleScene.h"

namespace MEIUN {

	class BattleUICharIcon : public HARIKEN::UIObject
	{
	public:

		void onCreate();
		void update();

	private:

		friend BattleScene;

		void setUnitIcon(const HARIKEN::Texture* unitIconTextureID);

	};

}