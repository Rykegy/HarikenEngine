#include "stdafx.h"
#include "BattleUIDescriptionBox.h"

using namespace MEIUN;

void MEIUN::BattleUIDescriptionBox::onCreate()
{

	setImg(getAssetFile("BATTLEUI")->getTexture("BattleUIMoveName.png"));

	setPosition(windowSize.x / 2, windowSize.y / 2);

	layer = 1;

	isActive = false;

}

void MEIUN::BattleUIDescriptionBox::update()
{
}
