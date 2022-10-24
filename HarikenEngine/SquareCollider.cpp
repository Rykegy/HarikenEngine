#include "stdafx.h"
#include "SquareCollider.h"

using namespace HARIKEN;

HARIKEN::SquareCollider::SquareCollider()
{

	type = SQUARE;

	pointOffsetFromPos.push_back(glm::vec3(0, 0, 0));
	pointOffsetFromPos.push_back(glm::vec3(0, 0, 0));
	pointOffsetFromPos.push_back(glm::vec3(0, 0, 0));
	pointOffsetFromPos.push_back(glm::vec3(0, 0, 0));

	posOffset = glm::vec3(0, 0, 0);

}

SquareCollider::SquareCollider(float w, float h, float offsetX, float offsetY)
{

	type = SQUARE;

	pointOffsetFromPos.push_back(glm::vec3(-w / 2, h / 2, 0));
	pointOffsetFromPos.push_back(glm::vec3(w / 2, h / 2, 0));
	pointOffsetFromPos.push_back(glm::vec3(w / 2, -h / 2, 0));
	pointOffsetFromPos.push_back(glm::vec3(-w / 2, -h / 2, 0));

	posOffset = glm::vec3(offsetX, offsetY, 0);

}

HARIKEN::SquareCollider::SquareCollider(float w, float h, glm::vec2 offset)
{

	type = SQUARE;

	pointOffsetFromPos.push_back(glm::vec3(-w / 2, h / 2, 0));
	pointOffsetFromPos.push_back(glm::vec3(w / 2, h / 2, 0));
	pointOffsetFromPos.push_back(glm::vec3(w / 2, -h / 2, 0));
	pointOffsetFromPos.push_back(glm::vec3(-w / 2, -h / 2, 0));

	posOffset = glm::vec3(offset.x, offset.y, 0);

}

SquareCollider::~SquareCollider()
{



}