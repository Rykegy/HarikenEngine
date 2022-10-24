#include "stdafx.h"
#include "BattleUIEnemyStatusBox.h"

using namespace MEIUN;

void MEIUN::BattleUIEnemyStatusBox::onCreate()
{

	setImg(getAssetFile("BATTLEUI")->getTexture("BattleUIEnemyStatus.png"));

	setPosition(windowSize.x / 2, windowSize.y / 2);

	layer = 2;

}

void MEIUN::BattleUIEnemyStatusBox::update()
{
}
