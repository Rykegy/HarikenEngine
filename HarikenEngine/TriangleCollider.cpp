#include "stdafx.h"
#include "TriangleCollider.h"

using namespace HARIKEN;

TriangleCollider::TriangleCollider()
{

	posOffset = glm::vec3(0, 0, 0);

	pointOffsetFromPos.push_back(glm::vec3(0.0f));
	pointOffsetFromPos.push_back(glm::vec3(0.0f));
	pointOffsetFromPos.push_back(glm::vec3(0.0f));

}

TriangleCollider::TriangleCollider(glm::vec2 point1, glm::vec2 point2, glm::vec2 point3, glm::vec3 offset)
{

	posOffset = offset;

	pointOffsetFromPos.push_back(glm::vec3(point1.x, point1.y, 0.0f));
	pointOffsetFromPos.push_back(glm::vec3(point2.x, point2.y, 0.0f));
	pointOffsetFromPos.push_back(glm::vec3(point3.x, point3.y, 0.0f));

}

TriangleCollider::TriangleCollider(glm::vec2 point1, glm::vec2 point2, glm::vec2 point3, float offsetX, float offsetY)
{

	posOffset = glm::vec3(offsetX, offsetY, 0.0f);

	pointOffsetFromPos.push_back(glm::vec3(point1.x, point1.y, 0.0f));
	pointOffsetFromPos.push_back(glm::vec3(point2.x, point2.y, 0.0f));
	pointOffsetFromPos.push_back(glm::vec3(point3.x, point3.y, 0.0f));

}

TriangleCollider::~TriangleCollider()
{
}
