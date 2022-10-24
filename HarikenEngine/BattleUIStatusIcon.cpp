#include "stdafx.h"
#include "BattleUIStatusIcon.h"

using namespace MEIUN;

void MEIUN::BattleUIStatusIcon::onCreate()
{

	setPosition(windowSize.x / 2, windowSize.y / 2 + 260.0f);
	setScale(glm::vec3(1.0f / 3.0f, 1.0f / 3.0f, 1.0f));

	layer = 3;

}

void MEIUN::BattleUIStatusIcon::update()
{
}

void MEIUN::BattleUIStatusIcon::setUnitIcon(const HARIKEN::Texture * unitIconTextureID)
{

	setImg(unitIconTextureID);

}
