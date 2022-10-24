#include "stdafx.h"
#include "BattleUIPlayerStatusBox.h"

using namespace MEIUN;

void MEIUN::BattleUIPlayerStatusBox::onCreate()
{

	setImg(getAssetFile("BATTLEUI")->getTexture("BattleUIPlayerStatus.png"));

	setPosition(windowSize.x / 2, windowSize.y / 2);

	layer = 2;

}

void MEIUN::BattleUIPlayerStatusBox::update()
{
}
