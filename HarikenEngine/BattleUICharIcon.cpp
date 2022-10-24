#include "stdafx.h"
#include "BattleUICharIcon.h"

using namespace MEIUN;

void MEIUN::BattleUICharIcon::onCreate()
{

	setPosition(90.0f, 90.0f);
	layer = 1;

}

void MEIUN::BattleUICharIcon::update()
{

}

void MEIUN::BattleUICharIcon::setUnitIcon(const HARIKEN::Texture * unitIconTextureID)
{

	setImg(unitIconTextureID);

}
