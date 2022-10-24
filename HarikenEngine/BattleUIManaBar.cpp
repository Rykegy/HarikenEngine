#include "stdafx.h"
#include "BattleUIManaBar.h"

using namespace MEIUN;

void MEIUN::BattleUIManaBar::onCreate()
{

	setImg(getAssetFile("BATTLEUI")->getTexture("ManaBar.png"));
	setPosition(windowSize.x / 2, windowSize.y / 2 + 245.0f);
	alignment.vertical = Align::center;
	alignment.horizontal = Align::left;
	setScale(glm::vec3(1.0f, 0.13f, 1.0f));
	layer = 1;

}

void MEIUN::BattleUIManaBar::update()
{

	if (newMana != currentMana) {

		currentMana -= deductionRate * time->deltaTime;

		if (currentMana < newMana && deductionRate > 0)
			currentMana = newMana;

		else if(currentMana > newMana && deductionRate < 0)
			currentMana = newMana;

		setScale(glm::vec3(currentMana / initialMana, 0.13f, 1.0f));

	}

}

void MEIUN::BattleUIManaBar::setInitialMana(float MP)
{

	initialMana = MP;
	newMana = MP;
	currentMana = initialMana;

}

void MEIUN::BattleUIManaBar::subtractMana(float cost)
{

	newMana -= cost;

	deductionRate = cost / 1;

	if (newMana < 0)
		newMana = 0;

}
