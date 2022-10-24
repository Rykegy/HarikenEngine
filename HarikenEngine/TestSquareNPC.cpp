#include "stdafx.h"
#include "TestSquareNPC.h"

using namespace HARIKEN;

void TestSquareNPC::onCreate()
{

	//collider = new CircleCollider(1, glm::vec2(0,0));
	//collider = new TriangleCollider(glm::vec2(0,0),glm::vec2(1,1),glm::vec2(-1,-1),glm::vec2(1,-1));

	setImg(getAssetFile("TMPASSETS")->getTexture("TestSquare.png"));
	kinematic = true;

}

void TestSquareNPC::update()
{
}
