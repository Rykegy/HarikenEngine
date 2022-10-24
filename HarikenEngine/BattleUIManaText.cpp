#include "stdafx.h"
#include "BattleUIManaText.h"

using namespace MEIUN;

void MEIUN::BattleUIManaText::onCreate()
{

	setFont("YuGothB.ttc");
	setText("Test", 16, glm::vec3(1.0f, 1.0f, 1.0f));
	setPosition(0.0f, 240.0f);
	alignment.vertical = Align::center;
	alignment.horizontal = Align::center;
	layer = 0;

}

void MEIUN::BattleUIManaText::update()
{
}
