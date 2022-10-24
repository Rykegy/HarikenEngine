#include "stdafx.h"
#include "BattleUIDescriptionText.h"

using namespace MEIUN;

void MEIUN::BattleUIDescriptionText::onCreate()
{

	setFont("YuGothB.ttc");
	setText("", 20, glm::vec3(1.0f, 1.0f, 1.0f));
	setPosition(0.0f, 325.0f);
	alignment.vertical = Align::center;
	alignment.horizontal = Align::center;
	layer = 0;

}

void MEIUN::BattleUIDescriptionText::update()
{
}
