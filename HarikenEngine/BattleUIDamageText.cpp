#include "stdafx.h"
#include "BattleUIDamageText.h"

using namespace MEIUN;

void MEIUN::BattleUIDamageText::onCreate()
{

	setFont("YuGothB.ttc");
	setText("", 48, glm::vec3(1.0f, 0.1f, 0.0f));
	setPosition(0.0f, 175.0f);
	alignment.vertical = Align::center;
	alignment.horizontal = Align::center;
	layer = 0;

}

void MEIUN::BattleUIDamageText::update()
{
}
