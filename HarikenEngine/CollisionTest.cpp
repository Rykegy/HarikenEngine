#include "stdafx.h"
#include "CollisionTest.h"

using namespace HARIKEN;

CollisionTest::CollisionTest()
{

	bgColor = glm::vec3(1.0f, 1.0f, 1.0f);

}


CollisionTest::~CollisionTest()
{
}

void HARIKEN::CollisionTest::onCreate()
{

	Player = new TestSquare();
	Obstacle = new TestSquareNPC();

	addObject(Player, "Player");
	addObject(Obstacle, "Obstacle");

}

void HARIKEN::CollisionTest::onStart()
{

	Player->setPos(5.0f, 3.5f);
	Player->setGravity(false);
	Obstacle->setPos(10.0f, 3.5f);
	Obstacle->addCollider(new BoundingCollider(Obstacle->model[0], glm::vec3(0.0f), true));

}
