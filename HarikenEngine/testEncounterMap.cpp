#include "stdafx.h"
#include "testEncounterMap.h"
#include "TestSquareNPC.h"
#include "TestSquareNPCGreen.h"
#include "HoodedNaracuva.h"
#include "tutPicture.h"

using namespace MEIUN;

void MEIUN::testEncounterMap::onCreate()
{

	Player->setPos(0.0f, 0.0f);

	gravity = -9.8f * 4;

	platform0 = new HARIKEN::TestSquareNPC();
	platform1 = new HARIKEN::TestSquareNPC();
	platform2 = new HARIKEN::TestSquareNPC();
	platform3 = new HARIKEN::TestSquareNPC();

	TriggerPoint = new HARIKEN::TestSquareNPCGreen();

	addObject(static_cast<HARIKEN::GameObject*>(Player), "Player");
	addObject(platform0, "Ground");
	addObject(platform1, "Wall");
	addObject(platform2, "Wall");
	addObject(platform3, "Ground");
	addObject(TriggerPoint, "EnemyEncounter");
	addObject(new tutPicture(), "Tutorial Control Image");

	addEnemy(new HoodedNaracuva());

}

void MEIUN::testEncounterMap::onStart()
{

	platform0->setPos(-1.5f, -2.5f);
	platform0->setScale(glm::vec3(20.0f, 1.0f, 1.0f));
	platform0->addCollider(new HARIKEN::BoundingCollider(platform0->model[0], glm::vec3(0.0f), true));

	platform1->setPos(-11.0f, 1.5f);
	platform1->setScale(glm::vec3(1.0f, 8.0f, 1.0f));
	platform1->addCollider(new HARIKEN::BoundingCollider(platform1->model[0], glm::vec3(0.0f), true));

	platform2->setPos(8.0f, 1.5f);
	platform2->setScale(glm::vec3(1.0f, 8.0f, 1.0f));
	platform2->addCollider(new HARIKEN::BoundingCollider(platform2->model[0], glm::vec3(0.0f), true));

	platform3->setPos(-1.5f, 5.5f);
	platform3->setScale(glm::vec3(20.0f, 1.0f, 1.0f));
	platform3->addCollider(new HARIKEN::BoundingCollider(platform3->model[0], glm::vec3(0.0f), true));

	TriggerPoint->setPos(-8.5f, 0.0f);
	TriggerPoint->setScale(glm::vec3(2.0f, 4.0f, 1.0f));
	TriggerPoint->addCollider(new HARIKEN::BoundingCollider(TriggerPoint->model[0], glm::vec3(0.0f), true));
	TriggerPoint->Colliders[0]->isTrigger = true;
	TriggerPoint->layer = 1;

}
