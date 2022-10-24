#include "stdafx.h"
#include "BattleUIHealthBar.h"

using namespace HARIKEN;

void MEIUN::BattleUIHealthBar::onCreate()
{

	setImg(getAssetFile("BATTLEUI")->getTexture("HealthBar.png"));
	setPosition(windowSize.x / 2, windowSize.y / 2 + 275.0f);
	alignment.vertical = Align::center;
	alignment.horizontal = Align::left;
	setScale(glm::vec3(1.0f, 0.13f, 1.0f));
	layer = 1;

}

void MEIUN::BattleUIHealthBar::update()
{

	if (newHealth != currentHealth) {

		currentHealth -= deductionRate * time->deltaTime;

		if (currentHealth < newHealth && deductionRate > 0)
			currentHealth = newHealth;

		else if (currentHealth > newHealth && deductionRate < 0)
			currentHealth = newHealth;

		setScale(glm::vec3(currentHealth / initialHealth, 0.13f, 1.0f));

	}

}

void MEIUN::BattleUIHealthBar::setInitialHealth(float HP)
{

	initialHealth = HP;
	newHealth = HP;
	currentHealth = initialHealth;

}

void MEIUN::BattleUIHealthBar::subtractHealth(float damage)
{

	newHealth -= damage;

	deductionRate = damage / 1;

	if (newHealth < 0)
		newHealth = 0;

}
