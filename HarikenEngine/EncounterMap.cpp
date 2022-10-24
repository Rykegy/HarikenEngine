#include "stdafx.h"
#include "EncounterMap.h"

using namespace MEIUN;

EncounterMap::EncounterMap()
{

	bgColor = glm::vec3(1.0f, 1.0f, 1.0f);

}

EncounterMap::~EncounterMap()
{

	for (size_t i = 0; i < Enemies.size(); i++)
		Enemies[i]->Destroy();

}

Unit * MEIUN::EncounterMap::getEnemy(int enemyIndex) // Get a specific enemy from a list of possible enemies that can be encountered
{

	if (enemyIndex >= Enemies.size() || enemyIndex < 0)
		return nullptr;

	else
		return Enemies[enemyIndex];

}

Unit* MEIUN::EncounterMap::getRandomEnemy() // Get a random enemy from a list of possible enemies that can be encountered
{

	distribution = std::uniform_int_distribution<int>(0, Enemies.size() - 1);

	return Enemies[distribution(generator)];

}

battleResult MEIUN::EncounterMap::startBattle() // Initiate a battle sequence with a random enemy
{

	battleResult result;

	battleScene = new BattleScene();
	battleScene->startBattle(Player->unit, getRandomEnemy(), &result);
	delete battleScene;

	return result;

}

battleResult MEIUN::EncounterMap::startBattle(Unit * enemy) // Initiate a battle sequence with a specific enemy
{

	battleResult result;

	if (enemy == nullptr)
		enemy = getRandomEnemy();

	battleScene->startBattle(Player->unit, enemy, &result);
	delete battleScene;

	return result;

}

void MEIUN::EncounterMap::addEnemy(Unit * enemy) // Add an enemy unit to the list of possible encounters
{

	Enemies.push_back(enemy);

}

void MEIUN::EncounterMap::setBattleBGM(HARIKEN::Sound * BGM) // Set BGM to be used for battles that occur on this stage
{

	battleScene->setBGM(BGM);

}
