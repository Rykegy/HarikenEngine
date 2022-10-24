#include "stdafx.h"
#include "BattleUISkill.h"
#include "BattleScene.h"

using namespace MEIUN;

MEIUN::BattleUISkill::BattleUISkill(const Skill* skill_, int skillNumber_)
{

	skill = skill_;
	skillNumber = skillNumber_;

}

void MEIUN::BattleUISkill::onCreate()
{

	setFont("YuGothB.ttc");

	name = skill->name;
	description = skill->description;

	if (skill->getLanguageOption() != nullptr) {
		name = skill->getLanguageOption()->name;
		description = skill->getLanguageOption()->description;
	}

	setText(name, 24, glm::vec3(1.0f, 1.0f, 1.0f));

	setPosition(410.0f, 90.0f - 50 * skillNumber);
	alignment.vertical = Align::bottom;
	alignment.horizontal = Align::left;
	layer = 0;

	isActive = false;

	descriptionText = GameScene->findUIObjectWithTag("DescriptionText");
	descriptionBox = GameScene->findUIObjectWithTag("DescriptionBox");

	battleScene = static_cast<BattleScene*>(GameScene);

}

void MEIUN::BattleUISkill::update()
{
	
	if (onMouseOver()) {

		descriptionText->setText(description, 18, glm::vec3(1.0f, 1.0f, 1.0f));
		descriptionBox->isActive = true;
		mouseOvered = true;

	}

	else if (!onMouseOver() && mouseOvered) {

		mouseOvered = false;
		descriptionText->setText("", 18, glm::vec3(1.0f, 1.0f, 1.0f));
		descriptionBox->isActive = false;

	}

	if (onClick()) {

		battleScene->Player->useSkill(skill);

	}
	
}
