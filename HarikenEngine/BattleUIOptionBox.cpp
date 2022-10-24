#include "stdafx.h"
#include "BattleUIOptionBox.h"

using namespace MEIUN;

void MEIUN::BattleUIOptionBox::onCreate()
{

	setImg(getAssetFile("BATTLEUI")->getTexture("BattleUIOption.png"));

	setPosition(windowSize.x / 2, windowSize.y / 2);

	layer = 1;

	isActive = false;

}

void MEIUN::BattleUIOptionBox::update()
{
}
