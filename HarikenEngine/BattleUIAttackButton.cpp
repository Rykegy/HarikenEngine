#include "stdafx.h"
#include "BattleUIAttackButton.h"

using namespace MEIUN;

void MEIUN::BattleUIAttackButton::onCreate()
{

	setFont("YuGothB.ttc");
	switch (language) {

	case JP:
		setText(u"アタック", 40, glm::vec3(1.0f, 1.0f, 1.0f));
		break;

	default:
		setText("Attack", 40, glm::vec3(1.0f, 1.0f, 1.0f));
		break;

	}
	setPosition(290.0f, -260.0f);
	alignment.vertical = Align::bottom;
	alignment.horizontal = Align::left;
	layer = 0;

}

void MEIUN::BattleUIAttackButton::update()
{

	if (onClick())
		click = true;

	else
		click = false;

}
