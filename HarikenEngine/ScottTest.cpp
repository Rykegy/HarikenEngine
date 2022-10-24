#include "stdafx.h"
#include "ScottTest.h"
#include "skull.h"
//#include "Dice.h"
//#include "Cube.h"
//#include "Apple.h"

using namespace HARIKEN;

void HARIKEN::ScottTest::onCreate()
{

	bgColor = glm::vec3(1.0f, 1.0f, 1.0f);

	twoD = false;

	skullObj = new skull();

	addObject(skullObj, "Skull");

	//skyboxObj = nullptr;
	/*
	addObject(new Apple(), "apple");
	addObject(new Dice(), "dice");
	*/
}

void HARIKEN::ScottTest::onStart()
{

	//skullObj->setScale(glm::vec3(0.5f, 0.5f, 0.5f));

}
