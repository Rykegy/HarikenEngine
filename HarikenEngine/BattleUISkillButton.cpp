#include "stdafx.h"
#include "BattleUISkillButton.h"

void MEIUN::BattleUISkillButton::onCreate()
{

	setFont("YuGothB.ttc");
	switch (language) {

	case JP:
		setText(u"ÉXÉLÉã", 40, glm::vec3(1.0f, 1.0f, 1.0f));
		break;

	default:
		setText("Skill", 40, glm::vec3(1.0f, 1.0f, 1.0f));
		break;

	}
	setPosition(485.0f, -260.0f);
	alignment.vertical = Align::bottom;
	alignment.horizontal = Align::left;
	layer = 0;

}

void MEIUN::BattleUISkillButton::update()
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
