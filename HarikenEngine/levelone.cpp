#include "stdafx.h"
#include "levelone.h"
#include "TestSquare.h"
#include "TestSquareNPC.h"
#include "respawner.h"

using namespace HARIKEN;

levelone::levelone()
{
	gravity = gravity * 2;
	bgColor = glm::vec3(1.0f, 1.0f, 1.0f);

}

levelone::~levelone()
{
}

void HARIKEN::levelone::onCreate()
{

	Test = new TestSquare();
	platform0 = new TestSquareNPC();
	platform1 = new TestSquareNPC();
	door = new TestSquareNPC();
	coin0 = new TestSquareNPC();
	coin1 = new TestSquareNPC();
	coin2 = new TestSquareNPC();
	//respawn = new respawner();

	addObject(Test, "Test");
	addObject(platform0, "Platform 0");
	addObject(platform1, "Platform 1");
	addObject(door, "door");
	addObject(coin0, "coin 0");
	addObject(coin1, "coin 1");
	addObject(coin2, "coin 2");
	//objects.push_back(respawn);

}

void levelone::onStart() {

	Test->setPos(8, 2);
	platform0->setPos(8, 0);
	platform0->setScale(glm::vec3(16, 1, 0.0f));
	platform0->addCollider(new BoundingCollider(platform0->model[0], glm::vec3(0.0f), true));
	platform0->addTag("Ground");
	platform1->setPos(12, 2);
	platform1->setScale(glm::vec3(5, 0.5, 0.0f));
	platform1->addCollider(new BoundingCollider(platform1->model[0], glm::vec3(0.0f), true));
	platform1->addTag("Ground");
	door->setPos(2, 1);
	door->setScale(glm::vec3(2, 3, 0));
	door->addCollider(new BoundingCollider(door->model[0], glm::vec3(0.0f), true));
	door->addTag("Door");
	door->Colliders[0]->isTrigger = true;
	coin0->setPos(12, 3);
	coin0->setScale(glm::vec3(0.25, 0.5, 0.0f));
	coin0->addCollider(new BoundingCollider(coin0->model[0], glm::vec3(0.0f), true));
	coin0->addTag("Coin");
	coin0->Colliders[0]->isTrigger = true;
	coin1->setPos(11, 3);
	coin1->setScale(glm::vec3(0.25, 0.5, 0.0f));
	coin1->addCollider(new BoundingCollider(coin1->model[0], glm::vec3(0.0f), true));
	coin1->addTag("Coin");
	coin1->Colliders[0]->isTrigger = true;
	coin2->setPos(13, 3);
	coin2->setScale(glm::vec3(0.25, 0.5, 0.0f));
	coin2->addCollider(new BoundingCollider(coin2->model[0], glm::vec3(0.0f), true));
	coin2->addTag("Coin");
	coin2->Colliders[0]->isTrigger = true;
	//respawn->setPos(0, -2);
	//respawn->addTag("Ground");
	//respawn->addCollider(new SquareCollider(1000, 1, glm::vec2(0, 0)));

}
