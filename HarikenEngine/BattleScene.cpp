#include "stdafx.h"
#include "BattleScene.h"
#include "BattleUITextbox.h"
#include "BattleUICharIcon.h"
#include "BattleUICharIconFrame.h"
#include "BattleUIActionBox.h"
#include "BattleUIAttackButton.h"
#include "BattleUITechButton.h"
#include "BattleUISkillButton.h"
#include "BattleUIRunButton.h"
#include "BattleUIOptionBox.h"
#include "BattleUIText.h"
#include "BattleUIDescriptionBox.h"
#include "BattleUIDescriptionText.h"
#include "BattleUIDamageText.h"
#include "BattleUIhealthText.h"
#include "BattleUIManaText.h"
#include "BattleUIPlayerStatusBox.h"
#include "BattleUIEnemyStatusBox.h"
#include "BattleUIStatusIcon.h"
#include "Black.h"
#include "HoodedNaracuva.h"
#include "EncounterMap.h"
#include "NiftyConversions.h"

using namespace MEIUN;

void MEIUN::BattleScene::startBattle(Unit * Player_, Unit * Enemy_, battleResult* result_)
{
	//Set combatants to be used in the battle
	result = result_;

	windowSys = HARIKEN::WindowSys::GetInstance();

	Player = Player_;
	Enemy = Enemy_->clone();

	bgColor = glm::vec3(1.0f, 1.0f, 1.0f);

	HARIKEN::SceneManager::GetInstance()->setCutInScene(this, &isBattleOver);

}

void MEIUN::BattleScene::onCreate()
{
	//Set up all the UI required and initializes the combatants
	addObject(Player, "Player");
	addObject(Enemy, "Enemy");
	
	inputSys = HARIKEN::InputSys::GetInstance();

	attackButton = new BattleUIAttackButton();
	skillButton = new BattleUISkillButton();
	techButton = new BattleUITechButton();
	runButton = new BattleUIRunButton();

	battleText = new BattleUIText();

	descriptionBox = new BattleUIDescriptionBox();
	descriptionText = new BattleUIDescriptionText();

	damageTextEnemy = new BattleUIDamageText();
	damageTextPlayer = new BattleUIDamageText();

	playerHealth = new BattleUIHealthBar();
	playerMana = new BattleUIManaBar();
	playerHealthText = new BattleUIHealthText();
	playerManaText = new BattleUIManaText();

	enemyHealth = new BattleUIHealthBar();
	enemyMana = new BattleUIManaBar();
	enemyHealthText = new BattleUIHealthText();
	enemyManaText = new BattleUIManaText();

	addUI(new BattleUITextbox(), "BattleTextBox");
	addUI(new BattleUICharIcon(), "CharIcon");
	addUI(new BattleUICharIconFrame(), "CharIconFrame");
	addUI(new BattleUIActionBox(), "ActionBox");
	addUI(attackButton, "AttackButton");
	addUI(techButton, "TechButton");
	addUI(skillButton, "SkillButton");
	addUI(runButton, "RunButton");
	addUI(new BattleUIOptionBox(), "OptionBox");
	addUI(battleText, "BattleText");
	addUI(descriptionBox, "DescriptionBox");
	addUI(descriptionText, "DescriptionText");
	addUI(damageTextEnemy, "DamageTextEnemy");
	addUI(damageTextPlayer, "DamageTextPlayer");
	addUI(playerHealth, "PlayerHealthBar");
	addUI(playerMana, "PlayerManaBar");
	addUI(playerHealthText, "PlayerHealthText");
	addUI(playerManaText, "PlayerManaText");
	addUI(enemyHealth, "EnemyHealthBar");
	addUI(enemyMana, "EnemyManaBar");
	addUI(enemyHealthText, "EnemyHealthText");
	addUI(enemyManaText, "EnemyManaText");
	addUI(new BattleUIPlayerStatusBox(), "PlayerStatusBox");
	addUI(new BattleUIEnemyStatusBox(), "EnemyStatusBox");
	addUI(new BattleUIStatusIcon(), "PlayerStatusIcon");
	addUI(new BattleUIStatusIcon(), "EnemyStatusIcon");

	isBattleOver = false;

}
#include "Camera.h"
void MEIUN::BattleScene::onStart()
{
	//Prepares the layout of all the Objects
	damageTextEnemy->setPosition(damageTextEnemy->getPosition() - glm::vec2(220.0f, 0.0f));
	damageTextPlayer->setPosition(damageTextPlayer->getPosition() + glm::vec2(220.0f, 0.0f));

	playerHealth->setPosition(playerHealth->getPosition() + glm::vec2(575.0f, 0.0f));
	playerHealth->alignment.horizontal = HARIKEN::UIObject::Align::right;
	playerHealth->setInitialHealth(Player->HP);
	playerMana->setPosition(playerMana->getPosition() + glm::vec2(575.0f, 0.0f));
	playerMana->alignment.horizontal = HARIKEN::UIObject::Align::right;
	playerMana->setInitialMana(Player->MP);
	playerHealthText->setPosition(playerHealthText->getPosition() + glm::vec2(500.0f, 0.0f));
	playerHealthText->setText(std::to_string(Player->HP), 16, glm::vec3(1.0f, 1.0f, 1.0f));
	playerManaText->setPosition(playerManaText->getPosition() + glm::vec2(500.0f, 0.0f));
	playerManaText->setText(std::to_string(Player->MP), 16, glm::vec3(1.0f, 1.0f, 1.0f));

	enemyHealth->setPosition(enemyHealth->getPosition() - glm::vec2(575.0f, 0.0f));
	enemyHealth->setInitialHealth(Enemy->HP);
	enemyMana->setPosition(enemyMana->getPosition() - glm::vec2(575.0f, 0.0f));
	enemyMana->setInitialMana(Enemy->MP);
	enemyHealthText->setPosition(enemyHealthText->getPosition() - glm::vec2(500.0f, 0.0f));
	enemyHealthText->setText(std::to_string(Enemy->HP), 16, glm::vec3(1.0f, 1.0f, 1.0f));
	enemyManaText->setPosition(enemyManaText->getPosition() - glm::vec2(500.0f, 0.0f));
	enemyManaText->setText(std::to_string(Enemy->MP), 16, glm::vec3(1.0f, 1.0f, 1.0f));

	Player->unitInit();
	Enemy->unitInit();

	Player->layer = 1;
	Enemy->layer = 2;
	Enemy->willRender = false;

	for (size_t i = 0; i < Player->getSkillList()->size(); i++){
		addSkill(new BattleUISkill(Player->getSkillList()->at(i), i));
		addUI(skills[i], "Skill" + i);
	}

	for (size_t i = 0; i < Player->getTechList()->size(); i++) {
		addTech(new BattleUITech(Player->getTechList()->at(i), i));
		addUI(techs[i], "Tech" + i);
	}

	BattleUIStatusIcon* temp;

	temp = static_cast<BattleUIStatusIcon*>(findUIObjectWithTag("PlayerStatusIcon"));
	temp->setUnitIcon(Player->getUnitIcon());
	temp->setPosition(temp->getPosition() + glm::vec2(610.0f, 0.0f));
	temp = static_cast<BattleUIStatusIcon*>(findUIObjectWithTag("EnemyStatusIcon"));
	temp->setUnitIcon(Enemy->getUnitIcon());
	temp->setPosition(temp->getPosition() - glm::vec2(610.0f, 0.0f));

}

void MEIUN::BattleScene::inflictDamage()
{
	//Damage calculation
	if (damageDealt)
		return;

	damageDealt = true;

	int damage = 0;
	float accuracy = 0;
	float critical = 1.0f;
	float consistancy = 10.0f / 100.0f;
	float turnConsistancyModifier;

	if (playerTurn) {

		if (Player->getState() == State::attack || Player->getState() == State::tech) {

			if (Player->willCrit())
				critical = 1.5f;

			turnConsistancyModifier = Player->turnConsistancyModifier;
			if (turnConsistancyModifier > 100.0f)
				turnConsistancyModifier = 100.0f;

			consistancy = consistancy - consistancy * turnConsistancyModifier / 100.0f;

			if (consistancy != 0) {

				consistancy *= Player->turnAttackValue;

				distribution = std::uniform_real_distribution<float>(0, consistancy);
				consistancy = distribution(generator);

				//consistancy = static_cast <int> (rand()) / (static_cast <float> (RAND_MAX / (consistancy)));

			}

			if (consistancy >= Player->turnAttackValue)
				consistancy = Player->turnAttackValue - 1;

			damage = (Player->turnAttackValue- consistancy) * critical - Enemy->turnDefenceValue;
			if (damage <= 0)
				damage = 1;

			distribution = std::uniform_real_distribution<float>(0, 1);
			float rando = distribution(generator);

			if ((1 + (Player->turnAccuracyModifier * rando) / 100) * Player->technique / 2 + Player->technique / 2 > Enemy->turnAgilityValue) {
				Enemy->HP -= damage;
				if (Enemy->HP < 0)
					Enemy->HP = 0;
				std::string temp = "";
				if (critical == 1.5f)
					temp = "Critical ";
				temp += std::to_string(damage);
				if(critical == 1.5)
					damageTextEnemy->setText(temp, 48, glm::vec3(1.0f, 0.1f, 0.0f));
				else
					damageTextEnemy->setText(temp, 48, glm::vec3(0.0f, 0.0f, 0.0f));
				enemyHealth->subtractHealth(damage);
				enemyHealthText->setText(std::to_string(Enemy->HP), 16, glm::vec3(1.0f, 1.0f, 1.0f));
			}

			else {

				Enemy->startDodge();
				damageTextEnemy->setText("Miss", 48, glm::vec3(0.0f, 1.0f, 0.2f));

			}

		}

	}
	
	else {

		if (Enemy->willCrit())
			critical = 1.5f;

		turnConsistancyModifier = Enemy->turnConsistancyModifier;
		if (turnConsistancyModifier > 100.0f)
			turnConsistancyModifier = 100.0f;

		consistancy = consistancy - consistancy * turnConsistancyModifier / 100.0f;

		if (consistancy != 0) {

			consistancy *= Enemy->turnAttackValue;
			distribution = std::uniform_real_distribution<float>(0, consistancy);
			consistancy = distribution(generator);

		}

		if (consistancy >= Enemy->turnAttackValue)
			consistancy = Enemy->turnAttackValue - 1;

		damage = (Enemy->turnAttackValue - consistancy) * critical - Player->turnDefenceValue;
		if (damage <= 0)
			damage = 1;

		distribution = std::uniform_real_distribution<float>(0, 1);
		float rando = distribution(generator);

		if ((1 + (Enemy->turnAccuracyModifier * rando) / 100) * Enemy->technique / 2 + Enemy->technique / 2 > Player->turnAgilityValue) {
			Player->HP -= damage;
			if (Player->HP < 0)
				Player->HP = 0;
			std::string temp = "";
			if (critical == 1.5f)
				temp = "Critical ";
			temp += std::to_string(damage);
			if(critical == 1.5f)
				damageTextPlayer->setText(temp, 48, glm::vec3(1.0f, 0.1f, 0.0f));
			else
				damageTextPlayer->setText(temp, 48, glm::vec3(0.0f, 0.0f, 0.0f));
			playerHealth->subtractHealth(damage);
			playerHealthText->setText(std::to_string(Player->HP), 16, glm::vec3(1.0f, 1.0f, 1.0f));
		}

		else {
			Player->startDodge();
			damageTextPlayer->setText("Miss", 48, glm::vec3(0.0f, 1.0f, 0.2f));
		}

	}

}

void MEIUN::BattleScene::manaCut(Unit * unit, int amount) //Used to deplete the mana of a combatant
{
	
	unit->MP -= amount;

	if (unit == Player) {

		playerMana->subtractMana(amount);
		playerManaText->setText(std::to_string(unit->MP), 16, glm::vec3(1.0f, 1.0f, 1.0f));

	}

	else if (unit == Enemy) {

		enemyMana->subtractMana(amount);
		enemyManaText->setText(std::to_string(unit->MP), 16, glm::vec3(1.0f, 1.0f, 1.0f));

	}

}

void MEIUN::BattleScene::HealthCut(Unit * unit, int amount) //Used to deplete the health of a combatant
{

	unit->HP -= amount;

	if (unit == Player) {

		playerHealth->subtractHealth(amount);
		playerHealthText->setText(std::to_string(unit->HP), 16, glm::vec3(1.0f, 1.0f, 1.0f));

	}

	else if (unit == Enemy) {

		enemyHealth->subtractHealth(amount);
		enemyHealthText->setText(std::to_string(unit->HP), 16, glm::vec3(1.0f, 1.0f, 1.0f));

	}

}

void MEIUN::BattleScene::switchTurn() //Switch battle phase
{

	if (Player->HP <= 0 || Enemy->HP <= 0) { //Battle is over if a combatant's health has been depleted completely

		isBattleOver = true;

		if (battleBGM != nullptr)
			if (battleBGM->isPlaying())
				battleBGM->stop();

		if (Player->HP > 0)
			* result = victory;

		else
			*result = defeat;

		return;

	}

	damageDealt = false;
	damageTextEnemy->setText("", 48, glm::vec3(1.0f, 0.1f, 0.0f));
	damageTextPlayer->setText("", 48, glm::vec3(1.0f, 0.1f, 0.0f));
	//Change the icon displayed depending on whose turn it currently is
	if (playerTurn) {
		static_cast<BattleUICharIcon*>(findUIObjectWithTag("CharIcon"))->setUnitIcon(Enemy->getUnitIcon());
		playerTurn = false;
		Enemy->turnStart();
		Enemy->Attack();
	}

	else {
		static_cast<BattleUICharIcon*>(findUIObjectWithTag("CharIcon"))->setUnitIcon(Player->getUnitIcon());
		playerTurn = true;
		Player->turnStart();
	}

}

void MEIUN::BattleScene::showOpponent()
{

	if (playerTurn) {
		Enemy->willRender = true;
	}

	else {
		Player->willRender = true;
	}

}

void MEIUN::BattleScene::setBGM(HARIKEN::Sound * battleBGM_) // Set BGM to be used for the battle
{

	battleBGM = battleBGM_;

}

void MEIUN::BattleScene::update()
{

	if (battleBGM != nullptr) {

		if (!battleBGM->isPlaying())
			battleBGM->play();

	}
	
	battleText->setText(Player->getBattleText(), 40, glm::vec3(1.0f, 1.0f, 1.0f));
	playerHealthText->setText(std::to_string(Player->HP), 16, glm::vec3(1.0f, 1.0f, 1.0f));
	enemyHealthText->setText(std::to_string(Enemy->HP), 16, glm::vec3(1.0f, 1.0f, 1.0f));

	if (Player->getState() == State::idle || Player->getState() == State::skill) {
	}
	else {
	}

	if (Enemy->getState() == State::idle || Enemy->getState() == State::skill) {
	}
	else {
	}

	if(playerTurn)
		static_cast<BattleUICharIcon*>(findUIObjectWithTag("CharIcon"))->setUnitIcon(Player->getUnitIcon());

	if (Player->getState() != State::idle || !playerTurn) {

		attackButton->isActive = false;
		skillButton->isActive = false;
		techButton->isActive = false;
		runButton->isActive = false;

	}

	else {

		attackButton->isActive = true;
		skillButton->isActive = true;
		techButton->isActive = true;
		runButton->isActive = true;

	}
	//Check player UI interaction
	if (inputSys->inputs.Click.leftclickdown) {

		if (static_cast<BattleUIAttackButton*>(attackButton)->click) {

			Player->Attack();

		}

		if (static_cast<BattleUISkillButton*>(skillButton)->click) {

			for (size_t i = 0; i < skills.size(); i++)
				skills[i]->isActive = true;

		}

		else {

			for (size_t i = 0; i < skills.size(); i++)
				skills[i]->isActive = false;

			descriptionText->setText("", 30, glm::vec3(1.0f, 1.0f, 1.0f));
			descriptionBox->isActive = false;

		}

		if (static_cast<BattleUITechButton*>(techButton)->click) {

			for (size_t i = 0; i < techs.size(); i++)
				techs[i]->isActive = true;

		}

		else {

			for (size_t i = 0; i < techs.size(); i++)
				techs[i]->isActive = false;

			descriptionText->setText("", 30, glm::vec3(1.0f, 1.0f, 1.0f));
			descriptionBox->isActive = false;

		}

		if (static_cast<BattleUIRunButton*>(runButton)->click) {

			isBattleOver = true;
			*result = escape;

		}

	}

}

void MEIUN::BattleScene::addSkill(BattleUISkill* newSkill)
{

	newSkill->init(this);
	skills.push_back(newSkill);

}

void MEIUN::BattleScene::addTech(BattleUITech* newTech)
{

	newTech->init(this);
	techs.push_back(newTech);

}
