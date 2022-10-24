#include "stdafx.h"
#include "BattleUIHealthText.h"

using namespace MEIUN;

void MEIUN::BattleUIHealthText::onCreate()
{

	setFont("YuGothB.ttc");
	setText("", 16, glm::vec3(1.0f, 1.0f, 1.0f));
	setPosition(0.0f, 270.0f);
	alignment.vertical = Align::center;
	alignment.horizontal = Align::center;
	layer = 0;

}

void MEIUN::BattleUIHealthText::update()
{
}
