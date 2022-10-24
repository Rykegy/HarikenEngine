#include "stdafx.h"
#include "BattleUIText.h"

using namespace MEIUN;

void MEIUN::BattleUIText::onCreate()
{

	setFont("YuGothB.ttc");
	setText("", 40, glm::vec3(1.0f, 1.0f, 1.0f));
	setPosition(-450.0f, -300.0f);
	alignment.vertical = Align::bottom;
	alignment.horizontal = Align::left;
	layer = 0;

}

void MEIUN::BattleUIText::update()
{
}
