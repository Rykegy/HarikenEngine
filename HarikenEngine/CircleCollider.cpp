#include "stdafx.h"
#include "CircleCollider.h"

using namespace HARIKEN;
#include<iostream>
HARIKEN::CircleCollider::CircleCollider()
{

	r = 0;
	posOffset = glm::vec3(0, 0, 0);
	
	pointOffsetFromPos.push_back(glm::vec3(r, 0, 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(22.5 * M_PI / 180), r * std::sin(22.5 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(45 * M_PI / 180), r * std::sin(45 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(67.5 * M_PI / 180), r * std::sin(67.5 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(90 * M_PI / 180), r * std::sin(90 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(112.5 * M_PI / 180), r * std::sin(112.5 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(135 * M_PI / 180), r * std::sin(135 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(157.5 * M_PI / 180), r * std::sin(157.5 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(180 * M_PI / 180), r * std::sin(180 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(202.5 * M_PI / 180), r * std::sin(202.5 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(225 * M_PI / 180), r * std::sin(225 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(247.5 * M_PI / 180), r * std::sin(247.5 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(270 * M_PI / 180), r * std::sin(270 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(292.5 * M_PI / 180), r * std::sin(292.5 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(315 * M_PI / 180), r * std::sin(315 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(337.5 * M_PI / 180), r * std::sin(337.5 * M_PI / 180), 0));

}

CircleCollider::CircleCollider(float radius, glm::vec2 offset)
{

	type = CIRCLE;

	r = radius;
	posOffset = glm::vec3(offset.x, offset.y, 0);

	pointOffsetFromPos.push_back(glm::vec3(r, 0, 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(22.5 * M_PI / 180), r * std::sin(22.5 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(45 * M_PI / 180), r * std::sin(45 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(67.5 * M_PI / 180), r * std::sin(67.5 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(90 * M_PI / 180), r * std::sin(90 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(112.5 * M_PI / 180), r * std::sin(112.5 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(135 * M_PI / 180), r * std::sin(135 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(157.5 * M_PI / 180), r * std::sin(157.5 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(180 * M_PI / 180), r * std::sin(180 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(202.5 * M_PI / 180), r * std::sin(202.5 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(225 * M_PI / 180), r * std::sin(225 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(247.5 * M_PI / 180), r * std::sin(247.5 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(270 * M_PI / 180), r * std::sin(270 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(292.5 * M_PI / 180), r * std::sin(292.5 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(315 * M_PI / 180), r * std::sin(315 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(337.5 * M_PI / 180), r * std::sin(337.5 * M_PI / 180), 0));

}

HARIKEN::CircleCollider::CircleCollider(float radius, float offsetX, float offsetY)
{

	type = CIRCLE;

	r = radius;
	posOffset = glm::vec3(offsetX, offsetY, 0);

	pointOffsetFromPos.push_back(glm::vec3(r, 0, 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(22.5 * M_PI / 180), r * std::sin(22.5 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(45 * M_PI / 180), r * std::sin(45 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(67.5 * M_PI / 180), r * std::sin(67.5 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(90 * M_PI / 180), r * std::sin(90 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(112.5 * M_PI / 180), r * std::sin(112.5 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(135 * M_PI / 180), r * std::sin(135 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(157.5 * M_PI / 180), r * std::sin(157.5 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(180 * M_PI / 180), r * std::sin(180 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(202.5 * M_PI / 180), r * std::sin(202.5 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(225 * M_PI / 180), r * std::sin(225 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(247.5 * M_PI / 180), r * std::sin(247.5 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(270 * M_PI / 180), r * std::sin(270 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(292.5 * M_PI / 180), r * std::sin(292.5 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(315 * M_PI / 180), r * std::sin(315 * M_PI / 180), 0));
	pointOffsetFromPos.push_back(glm::vec3(r * std::cos(337.5 * M_PI / 180), r * std::sin(337.5 * M_PI / 180), 0));

}

CircleCollider::~CircleCollider()
{
}
