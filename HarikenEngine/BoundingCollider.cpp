#include "stdafx.h"
#include "BoundingCollider.h"

using namespace HARIKEN;

BoundingCollider::BoundingCollider(Model* m)
{

	model = m;

	std::vector<vertex> vertices = m->getVertices();

	minX = INFINITY;
	minY = INFINITY;
	minZ = INFINITY;

	maxX = -INFINITY;
	maxY = -INFINITY;
	maxZ = -INFINITY;

	for (auto v : vertices) {

		if (v.position.x < minX)
			minX = v.position.x;
		if (v.position.y < minY)
			minY = v.position.y;
		if (v.position.z < minZ)
			minZ = v.position.z;

		if (v.position.x > maxX)
			maxX = v.position.x;
		if (v.position.y > maxY)
			maxY = v.position.y;
		if (v.position.z > maxZ)
			maxZ = v.position.z;

	}

	minX *= m->getScale().x;
	minY *= m->getScale().y;
	minZ *= m->getScale().z;

	maxX *= m->getScale().x;
	maxY *= m->getScale().y;
	maxZ *= m->getScale().z;

	pointOffsetFromPos.push_back(glm::vec3(minX, minY, minZ));
	pointOffsetFromPos.push_back(glm::vec3(minX, minY, maxZ));
	pointOffsetFromPos.push_back(glm::vec3(minX, maxY, minZ));
	pointOffsetFromPos.push_back(glm::vec3(minX, maxY, maxZ));
	pointOffsetFromPos.push_back(glm::vec3(maxX, minY, minZ));
	pointOffsetFromPos.push_back(glm::vec3(maxX, minY, maxZ));
	pointOffsetFromPos.push_back(glm::vec3(maxX, maxY, minZ));
	pointOffsetFromPos.push_back(glm::vec3(maxX, maxY, maxZ));

}

HARIKEN::BoundingCollider::BoundingCollider(Model * m, glm::vec3 offset)
{

	std::vector<vertex> vertices = m->getVertices();

	minX = INFINITY;
	minY = INFINITY;
	minZ = INFINITY;

	maxX = -INFINITY;
	maxY = -INFINITY;
	maxZ = -INFINITY;

	for (auto v : vertices) {

		if (v.position.x < minX)
			minX = v.position.x;
		if (v.position.y < minY)
			minY = v.position.y;
		if (v.position.z < minZ)
			minZ = v.position.z;

		if (v.position.x > maxX)
			maxX = v.position.x;
		if (v.position.y > maxY)
			maxY = v.position.y;
		if (v.position.z > maxZ)
			maxZ = v.position.z;

	}

	minX *= m->getScale().x;
	minY *= m->getScale().y;
	minZ *= m->getScale().z;

	maxX *= m->getScale().x;
	maxY *= m->getScale().y;
	maxZ *= m->getScale().z;

	pointOffsetFromPos.push_back(glm::vec3(minX, minY, minZ));
	pointOffsetFromPos.push_back(glm::vec3(minX, minY, maxZ));
	pointOffsetFromPos.push_back(glm::vec3(minX, maxY, minZ));
	pointOffsetFromPos.push_back(glm::vec3(minX, maxY, maxZ));
	pointOffsetFromPos.push_back(glm::vec3(maxX, minY, minZ));
	pointOffsetFromPos.push_back(glm::vec3(maxX, minY, maxZ));
	pointOffsetFromPos.push_back(glm::vec3(maxX, maxY, minZ));
	pointOffsetFromPos.push_back(glm::vec3(maxX, maxY, maxZ));

}

HARIKEN::BoundingCollider::BoundingCollider(Model* m, glm::vec3 offset, bool is2D)
{

	posOffset = offset;

	std::vector<vertex> vertices = m->getVertices();

	minX = INFINITY;
	minY = INFINITY;
	minZ = INFINITY;

	maxX = -INFINITY;
	maxY = -INFINITY;
	maxZ = -INFINITY;

	for (auto v : vertices) {

		if (v.position.x < minX)
			minX = v.position.x;
		if (v.position.y < minY)
			minY = v.position.y;
		if (v.position.z < minZ)
			minZ = v.position.z;

		if (v.position.x > maxX)
			maxX = v.position.x;
		if (v.position.y > maxY)
			maxY = v.position.y;
		if (v.position.z > maxZ)
			maxZ = v.position.z;

	}

	minX *= m->getScale().x;
	minY *= m->getScale().y;
	minZ *= m->getScale().z;

	maxX *= m->getScale().x;
	maxY *= m->getScale().y;
	maxZ *= m->getScale().z;

	if (is2D) {

		minX *= 0.0125f;
		minY *= 0.0125f;
		minZ = 0;

		maxX *= 0.0125f;
		maxY *= 0.0125f;
		maxZ = 0;

	}

	pointOffsetFromPos.push_back(glm::vec3(minX, minY, minZ));
	pointOffsetFromPos.push_back(glm::vec3(minX, minY, maxZ));
	pointOffsetFromPos.push_back(glm::vec3(minX, maxY, minZ));
	pointOffsetFromPos.push_back(glm::vec3(minX, maxY, maxZ));
	pointOffsetFromPos.push_back(glm::vec3(maxX, minY, minZ));
	pointOffsetFromPos.push_back(glm::vec3(maxX, minY, maxZ));
	pointOffsetFromPos.push_back(glm::vec3(maxX, maxY, minZ));
	pointOffsetFromPos.push_back(glm::vec3(maxX, maxY, maxZ));

}

BoundingCollider::~BoundingCollider()
{
}

Model * HARIKEN::BoundingCollider::getModel()
{
	return model;
}
