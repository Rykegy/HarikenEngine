#include "stdafx.h"
#include "TestSquareNPCGreen.h"

using namespace HARIKEN;

void TestSquareNPCGreen::onCreate()
{

	//collider = new CircleCollider(1, glm::vec2(0,0));
	//collider = new TriangleCollider(glm::vec2(0,0),glm::vec2(1,1),glm::vec2(-1,-1),glm::vec2(1,-1));

	setImg(getAssetFile("TMPASSETS")->getTexture("TestSquareGreen.png"));
	kinematic = true;

}

void TestSquareNPCGreen::update()
{
}