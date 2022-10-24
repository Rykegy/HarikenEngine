#include "stdafx.h"
#include "BattleUIRunButton.h"

using namespace MEIUN;

void MEIUN::BattleUIRunButton::onCreate()
{

	setFont("YuGothB.ttc");
	switch (language) {
	case JP:
		setText(u"“¦‚°‚é", 40, glm::vec3(1.0f, 1.0f, 1.0f));
		break;

	default:
		setText("Run", 40, glm::vec3(1.0f, 1.0f, 1.0f));
		break;
	}
	setPosition(485.0f, -345.0f);
	alignment.vertical = Align::bottom;
	alignment.horizontal = Align::left;
	layer = 0;

}

void MEIUN::BattleUIRunButton::update()
{

	if (onClick())
		click = true;

	else
		click = false;

}
