#include "stdafx.h"
#include "BattleUITech.h"
#include "BattleScene.h"

using namespace MEIUN;

MEIUN::BattleUITech::BattleUITech(const Tech * tech_, int techNumber_)
{

	tech = tech_;
	techNumber = techNumber_;

}

void MEIUN::BattleUITech::onCreate()
{

	setFont("YuGothB.ttc");

	name = tech->name;
	description = tech->description;

	if (tech->getLanguageOption() != nullptr) {
		name = tech->getLanguageOption()->name;
		description = tech->getLanguageOption()->description;
	}

	setText(name, 24, glm::vec3(1.0f, 1.0f, 1.0f));

	setPosition(410.0f, 90.0f - 50 * techNumber);
	alignment.vertical = Align::bottom;
	alignment.horizontal = Align::left;
	layer = 0;

	isActive = false;

	descriptionText = GameScene->findUIObjectWithTag("DescriptionText");
	descriptionBox = GameScene->findUIObjectWithTag("DescriptionBox");

	battleScene = static_cast<BattleScene*>(GameScene);

}

void MEIUN::BattleUITech::update()
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

		battleScene->Player->useTech(tech);

	}

}
