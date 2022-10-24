#include "stdafx.h"
#include "leveltwo.h"
#include "TestSquare.h"
#include "TestSquareNPC.h"
using namespace HARIKEN;

leveltwo::leveltwo()
{
	gravity = gravity * 2;
	bgColor = glm::vec3(1.0f, 1.0f, 1.0f);

}

leveltwo::~leveltwo()
{
}

void leveltwo::onCreate()
{

    Test = new TestSquare();
    platform0 = new TestSquareNPC();
    platform1 = new TestSquareNPC();
    platform2 = new TestSquareNPC();
    platform4 = new TestSquareNPC();
    platform5 = new TestSquareNPC();
    platform6 = new TestSquareNPC();
    platform7 = new TestSquareNPC();
    platform8 = new TestSquareNPC();
    platform9 = new TestSquareNPC();
    platform10 = new TestSquareNPC();
    platform11 = new TestSquareNPC();
    platform12 = new TestSquareNPC();
    platform13 = new TestSquareNPC();
    platform14 = new TestSquareNPC();
    platform15 = new TestSquareNPC();
    platform16 = new TestSquareNPC();
    platform17 = new TestSquareNPC();
    platform18 = new TestSquareNPC();
    door = new TestSquareNPC();
    coin0 = new TestSquareNPC();
    coin1 = new TestSquareNPC();
    coin2 = new TestSquareNPC();
    coin3 = new TestSquareNPC();
    coin4 = new TestSquareNPC();
    coin5 = new TestSquareNPC();
    coin6 = new TestSquareNPC();

    addObject(Test, "Test");
    addObject(platform0, "platform 0");
    addObject(platform1, "platform 1");
    addObject(platform2, "platform 2");
    addObject(platform4, "platform 3");
    addObject(platform5, "platform 4");
    addObject(platform6, "platform 5");
    addObject(platform7, "platform 6");
    addObject(platform8, "platform 7");
    addObject(platform9, "platform 8");
    addObject(platform10, "platform 9");
    addObject(platform11, "platform 10");
    addObject(platform12, "platform 12");
    addObject(platform13, "platform 13");
    addObject(platform14, "platform 14");
    addObject(platform15, "platform 15");
    addObject(platform16, "platform 16");
    addObject(platform17, "platform 17");
    addObject(platform18, "platform 18");
    addObject(door, "door");
    addObject(coin0, "coin 0");
    addObject(coin1, "coin 1");
    addObject(coin2, "coin 2");
    addObject(coin3, "coin 3");
    addObject(coin4, "coin 4");
    addObject(coin5, "coin 5");
    addObject(coin6, "coin 6");

}

void leveltwo::onStart() {

    Test->setPos(8, 5);
    platform0->setPos(8, 0);
	platform0->setScale(glm::vec3(16, 1, 0.0f));
	platform0->addCollider(new SquareCollider(16, 1, glm::vec2(0, 0)));
	platform0->addTag("Ground");
    platform1->setPos(16, 15.255);
    platform1->setScale(glm::vec3(1, 32, 0.0f));
    platform1->addCollider(new SquareCollider(1, 31, glm::vec2(0, 0)));
    platform1->addTag("Ground");
    platform2->setPos(-1, 19.1);
    platform2->setScale(glm::vec3(1, 40, 0.0f));
    platform2->addCollider(new SquareCollider(1, 40, glm::vec2(0, 0)));
    platform2->addTag("Ground");
    platform4->setPos(3, 21);
    platform4->setScale(glm::vec3(8, 1, 0.0f));
    platform4->addCollider(new SquareCollider(8, 1, glm::vec2(0, 0)));
    platform4->addTag("Ground");
    platform5->setPos(33, 28);
    platform5->setScale(glm::vec3(1, 16, 0.0f));
    platform5->addCollider(new SquareCollider(1, 16, glm::vec2(0, 0)));
    platform5->addTag("Ground");
    platform6->setPos(6.45, 26.75);
    platform6->setScale(glm::vec3(1, 12, 0.0f));
    platform6->addTag("Ground");
    platform6->addCollider(new SquareCollider(1, 12, glm::vec2(0, 0)));
    platform7->setPos(14, 28);
    platform7->setScale(glm::vec3(16, 1, 0.0f));
    platform7->addTag("Ground");
    platform7->addCollider(new SquareCollider(16, 1, glm::vec2(0, 0)));
    platform8->setPos(10, 2);
    platform8->setScale(glm::vec3(2, 0.5, 0.0f));
    platform8->addTag("Ground");
    platform8->addCollider(new SquareCollider(2, 0.5, glm::vec2(0, 0)));
    platform9->setPos(7, 4);
    platform9->setScale(glm::vec3(2, 0.5, 0.0f));
    platform9->addTag("Ground");
    platform9->addCollider(new SquareCollider(2, 0.5, glm::vec2(0, 0)));
    platform10->setPos(3, 6);
    platform10->setScale(glm::vec3(5, 0.5, 0.0f));
    platform10->addTag("Ground");
    platform10->addCollider(new SquareCollider(5, 0.5, glm::vec2(0, 0)));
    platform11->setPos(9, 8);
    platform11->setScale(glm::vec3(6, 0.5, 0.0f));
    platform11->addTag("Ground");
    platform11->addCollider(new SquareCollider(6, 0.5, glm::vec2(0, 0)));
    platform12->setPos(14, 10);
    platform12->setScale(glm::vec3(2, 0.5, 0.0f));
    platform12->addTag("Ground");
    platform12->addCollider(new SquareCollider(2, 0.5, glm::vec2(0, 0)));
    platform13->setPos(10, 12);
    platform13->setScale(glm::vec3(2, 0.5, 0.0f));
    platform13->addTag("Ground");
    platform13->addCollider(new SquareCollider(2, 0.5, glm::vec2(0, 0)));
    platform14->setPos(14, 14);
    platform14->setScale(glm::vec3(4, 0.5, 0.0f));
    platform14->addTag("Ground");
    platform14->addCollider(new SquareCollider(4, 0.5, glm::vec2(0, 0)));
    platform15->setPos(15, 16);
    platform15->setScale(glm::vec3(2, 0.5, 0.0f));
    platform15->addTag("Ground");
    platform15->addCollider(new SquareCollider(2, 0.5, glm::vec2(0, 0)));
    platform16->setPos(13, 18);
    platform16->setScale(glm::vec3(1, 0.5, 0.0f));
    platform16->addTag("Ground");
    platform16->addCollider(new SquareCollider(1, 0.5, glm::vec2(0, 0)));
    platform17->setPos(10, 20);
    platform17->setScale(glm::vec3(2, 0.5, 0.0f));
    platform17->addTag("Ground");
    platform17->addCollider(new SquareCollider(2, 0.5, glm::vec2(0, 0)));
    platform18->setPos(12, 22);
    platform18->setScale(glm::vec3(5, 0.5, 0.0f));
    platform18->addTag("Ground");
    platform18->addCollider(new SquareCollider(5, 0.5, glm::vec2(0, 0)));
    door->setPos(12,24);
    door->setScale(glm::vec3(2, 3, 0.0f));
    door->addCollider(new SquareCollider(3, 2, glm::vec2(0, 0)));
    door->addTag("Door");
    door->Colliders[0]->isTrigger = true;
    coin0->setPos(10, 3);
	coin0->setScale(glm::vec3(0.25, 0.5, 0.0f));
	coin0->addCollider(new SquareCollider(0.25, 0.5, glm::vec2(0, 0)));
	coin0->addTag("Coin");
	coin0->Colliders[0]->isTrigger = true;
    coin1->setPos(9, 9);
	coin1->setScale(glm::vec3(0.25, 0.5, 0.0f));
	coin1->addCollider(new SquareCollider(0.25, 0.5, glm::vec2(0, 0)));
	coin1->addTag("Coin");
	coin1->Colliders[0]->isTrigger = true;
    coin2->setPos(3, 7);
	coin2->setScale(glm::vec3(0.25, 0.5, 0.0f));
	coin2->addCollider(new SquareCollider(0.25, 0.5, glm::vec2(0, 0)));
	coin2->addTag("Coin");
	coin2->Colliders[0]->isTrigger = true;
    coin3->setPos(13, 19);
	coin3->setScale(glm::vec3(0.25, 0.5, 0.0f));
	coin3->addCollider(new SquareCollider(0.25, 0.5, glm::vec2(0, 0)));
	coin3->addTag("Coin");
	coin3->Colliders[0]->isTrigger = true;
    coin4->setPos(14, 15);
	coin4->setScale(glm::vec3(0.25, 0.5, 0.0f));
	coin4->addCollider(new SquareCollider(0.25, 0.5, glm::vec2(0, 0)));
	coin4->addTag("Coin");
	coin4->Colliders[0]->isTrigger = true;
    coin5->setPos(7, 5);
	coin5->setScale(glm::vec3(0.25, 0.5, 0.0f));
	coin5->addCollider(new SquareCollider(0.25, 0.5, glm::vec2(0, 0)));
	coin5->addTag("Coin");
	coin5->Colliders[0]->isTrigger = true;
    coin6->setPos(10, 21);
	coin6->setScale(glm::vec3(0.25, 0.5, 0.0f));
	coin6->addCollider(new SquareCollider(0.25, 0.5, glm::vec2(0, 0)));
	coin6->addTag("Coin");
	coin6->Colliders[0]->isTrigger = true;

}