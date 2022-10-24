#include "stdafx.h"
#include "TestSquare.h"
#include "SceneManager.h"
#include "WindowSys.h"

using namespace HARIKEN;

void TestSquare::onCreate()
{
	speed = 5;
	setLinearDamping(speed, speed);
	setImg(getAssetFile("TMPASSETS")->getTexture("TestSquare.png"));

	collider = new BoundingCollider(model[0], glm::vec3(1.0f, 1.0f, 0.0f), true);
	//collider = new CircleCollider(0.5, 0, 0);

	Colliders.push_back(collider);
	tag.push_back("Player");

	useGravity = true;

}
#include <iostream>
void TestSquare::update() {

	float deltaTime = time->deltaTime;

	float x = 0;
	float y = 0;

	bool ground = false;
	/*
	if (getMouseState() != "") {

		std::cout << getMouseState() << std::endl;
		std::cout << getMousePosition().x << ", " << getMousePosition().y << std::endl;

	}

	if(getMouseScroll().x != 0 && getMouseScroll().y != 0)
		std::cout << getMouseScroll().x << ", " << getMouseScroll().y << std::endl;
		*/
	for (size_t i = 0; i < collidedObjects.size(); i++) {
		if (collidedObjects[i]->hasTag("Ground"))
			ground = true;
		if (collidedObjects[i]->hasTag("Coin")) {
			collidedObjects[i]->Destroy();
		}

	}

	if (InputSys->inputs.onenterdown)
		for (size_t i = 0; i < collidedObjects.size(); i++)
			if (collidedObjects[i]->hasTag("Door"))
				sceneManager->loadLevel("Next");

	if (InputSys->inputs.left)
		x -= speed;

	if (InputSys->inputs.right)
		x += speed;
	/*
	if (InputSys->inputs.up)
		y += speed;

	if (InputSys->inputs.down)
		y -= speed;
	*/
	
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