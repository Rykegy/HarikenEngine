#include "stdafx.h"
#include "BattleUITechButton.h"

using namespace MEIUN;

void MEIUN::BattleUITechButton::onCreate()
{

	setFont("YuGothB.ttc");
	switch (language) {

	case JP:
		setText(u"•KŽE‹Z", 40, glm::vec3(1.0f, 1.0f, 1.0f));
		break;

	default:
		setText("Tech", 40, glm::vec3(1.0f, 1.0f, 1.0f));
		break;


	}
	setPosition(290.0f, -345.0f);
	alignment.vertical = Align::bottom;
	alignment.horizontal = Align::left;
	layer = 0;

}

void MEIUN::BattleUITechButton::update()
{

	if (onClick()) {

		click = true;

		if (opBox == nullptr)
			opBox = static_cast<BattleUIOptionBox*>(GameScene->findUIObjectWithTag("OptionBox"));

		if (!opBox->isActive)
			opBox->isActive = true;

	}

	else if (click && InputSys->inputs.Click.leftclickdown && !onClick()) {

		click = false;

		if (opBox == nullptr)
			opBox = static_cast<BattleUIOptionBox*>(GameScene->findUIObjectWithTag("OptionBox"));

		if (opBox->isActive)
			opBox->isActive = false;

	}

}
