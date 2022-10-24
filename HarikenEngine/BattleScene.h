/*********************************************
Battle scene that is shown during an enemy encounter.
*********************************************/

#pragma once
#include "Scene.h"
#include "Unit.h"
#include "UIObject.h"
#include "BattleUISkill.h"
#include "BattleUITech.h"
#include "BattleUIHealthBar.h"
#include "BattleUIManaBar.h"
#include <random>

namespace MEIUN {

	enum battleResult {

		victory,
		defeat,
		escape

	};

	class BattleScene : public HARIKEN::derivedScene<BattleScene>
	{

	public:

		void startBattle(Unit* Player, Unit* Enemy, battleResult* result);

		void onCreate();
		void onStart();

		std::string getName() {

			return "Battle Scene";

		}

		Unit* Player;
		Unit* Enemy;

		void inflictDamage();
		void manaCut(Unit*, int amount);
		void HealthCut(Unit*, int amount);

		void switchTurn();
		void showOpponent();

		void setBGM(HARIKEN::Sound* battleBGM);

	private:

		void update();

		std::default_random_engine generator;
		std::uniform_real_distribution<float> distribution;

		HARIKEN::InputSys* inputSys;

		bool isBattleOver = false;

		HARIKEN::UIObject* attackButton;
		HARIKEN::UIObject* skillButton;
		HARIKEN::UIObject* techButton;
		HARIKEN::UIObject* runButton;

		HARIKEN::UIObject* battleText;
		HARIKEN::UIObject* damageTextEnemy;
		HARIKEN::UIObject* damageTextPlayer;

		HARIKEN::UIObject* descriptionBox;
		HARIKEN::UIObject* descriptionText;

		BattleUIHealthBar* playerHealth;
		BattleUIManaBar* playerMana;
		HARIKEN::UIObject* playerHealthText;
		HARIKEN::UIObject* playerManaText;

		BattleUIHealthBar* enemyHealth;
		BattleUIManaBar* enemyMana;
		HARIKEN::UIObject* enemyHealthText;
		HARIKEN::UIObject* enemyManaText;

		std::vector<BattleUISkill*> skills;
		void addSkill(BattleUISkill*);

		std::vector<BattleUITech*>techs;
		void addTech(BattleUITech*);

		HARIKEN::Sound* battleBGM;

		bool playerTurn = true;
		bool damageDealt = false;

		float timer = 0.0f;

		battleResult* result;

	};

}