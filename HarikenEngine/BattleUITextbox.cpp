#include "stdafx.h"
#include "BattleUITextbox.h"

using namespace MEIUN;

void MEIUN::BattleUITextbox::onCreate()
{

	setImg(getAssetFile("BATTLEUI")->getTexture("BattleUIText.png"));

	setPosition(windowSize.x / 2, windowSize.y / 2);

	layer = 2;

}

void MEIUN::BattleUITextbox::update()
{
}