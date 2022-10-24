#include "stdafx.h"
#include "MapPlayer.h"
#include "BattleScene.h"
#include "EncounterMap.h"
#include "Black.h"

using namespace MEIUN;

void MEIUN::MapPlayer::onCreate()
{

	speed = 5;
	setLinearDamping(speed, speed);
	setImg(getAssetFile("TMPASSETS")->getTexture("TestSquare.png"));

	collider = new HARIKEN::BoundingCollider(model[0], glm::vec3(0.0f), true);
	addCollider(collider);

	useGravity = true;

	HARIKEN::GlobalObjectsHandler* globalObjects = HARIKEN::GlobalObjectsHandler::GetInstance();

	if (globalObjects->getGameObject("Player Unit") == nullptr) {

		Unit* playerUnit = new Black();
		playerUnit->init(nullptr);

		globalObjects->addGameObject(playerUnit, "Player Unit");

	}

	unit = static_cast<Unit*>(globalObjects->getGameObject("Player Unit"));

}

void MEIUN::MapPlayer::update() {

	float deltaTime = time->deltaTime;

	float x = 0;
	float y = 0;

	bool ground = false;

	for (size_t i = 0; i < collidedObjects.size(); i++) {
		if (collidedObjects[i]->hasTag("Ground"))
			ground = true;
		if (collidedObjects[i]->hasTag("EnemyEncounter") && iTimer <= 0) {

			velocity.x = 0;
			velocity.y = 0;
			acceleration.x = 0;
			acceleration.y = 0;
			battleResult result = static_cast<EncounterMap*>(GameScene)->startBattle();

			switch (result) {

			case victory:
				collidedObjects[i]->Destroy();
				break;

			case defeat:
				HARIKEN::GlobalObjectsHandler::GetInstance()->removeGameObject(unit);
				delete unit;
				sceneManager->loadLevel("Title Screen");
				break;

			case escape:
				iTimer = 2.0f;
				break;

			default:
				break;

			}

		}

	}

	if (iTimer > 0)
		iTimer -= deltaTime;

	if (InputSys->inputs.onenterdown)
		for (size_t i = 0; i < collidedObjects.size(); i++)
			if (collidedObjects[i]->hasTag("Door"))
				sceneManager->loadLevel("Next");

	if (InputSys->inputs.left)
		x -= speed;

	if (InputSys->inputs.right)
		x += speed;
	
	if (InputSys->inputs.onupdown && ground) {
		y = 15;
		jumpHeld = true;
	}

	if (InputSys->inputs.onupup)
		jumpHeld = false;

	if (jumpHeld == false && !ground && velocity.y > 0)
		addForce(glm::vec2(0.0f, -100.0f));

	if (x == 0)
		x = velocity.x;

	if (y == 0)
		y = velocity.y;
	
	setVelocity(x, y);

	glm::vec2 windowSize = Window->getWinSize();

	if (imagepos.x >= windowSize.x * 3 / 4)
		if (velocity.x > 0)
			GameScene->cameraPos.x += velocity.x * deltaTime - acceleration.x * std::pow(deltaTime, 2) / 2;
		else
			GameScene->cameraPos.x += 0.25;

	if (imagepos.x <= windowSize.x * 1 / 4)
		if(velocity.x < 0)
			GameScene->cameraPos.x += velocity.x * deltaTime - acceleration.x * std::pow(deltaTime, 2) / 2;
		else
			GameScene->cameraPos.x -= 0.25;

	if (imagepos.y >= windowSize.y * 3 / 4)
		if(velocity.y < 0)
			GameScene->cameraPos.y += velocity.y * deltaTime - acceleration.y * std::pow(deltaTime, 2) / 2;
		else
			GameScene->cameraPos.y -= 0.25;

	if (imagepos.y <= windowSize.y * 1 / 4)
		if(velocity.y > 0)
			GameScene->cameraPos.y += velocity.y * deltaTime - acceleration.y * std::pow(deltaTime, 2) / 2;
		else
			GameScene->cameraPos.y += 0.25;

}
