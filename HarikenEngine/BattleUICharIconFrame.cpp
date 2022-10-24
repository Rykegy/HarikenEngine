#include "stdafx.h"
#include "BattleUICharIconFrame.h"

using namespace MEIUN;

void MEIUN::BattleUICharIconFrame::onCreate()
{

	setImg(getAssetFile("BATTLEUI")->getTexture("BattleUIImage.png"));

	setPosition(windowSize.x / 2, windowSize.y / 2);

	layer = 0;

}

void MEIUN::BattleUICharIconFrame::update()
{
}
