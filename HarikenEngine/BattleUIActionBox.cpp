#include "stdafx.h"
#include "BattleUIActionBox.h"


void MEIUN::BattleUIActionBox::onCreate()
{

	setImg(getAssetFile("BATTLEUI")->getTexture("BattleUIAction.png"));

	setPosition(windowSize.x / 2, windowSize.y / 2);

	layer = 1;

}

void MEIUN::BattleUIActionBox::update()
{
}
