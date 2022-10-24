/**************
Triangle Collider.
**************/

#pragma once
#include "Collision.h"

namespace HARIKEN {

	class TriangleCollider : public Collision
	{
	public:
		TriangleCollider();
		TriangleCollider(glm::vec2 point1, glm::vec2 point2, glm::vec2 point3, glm::vec3 offset);
		TriangleCollider(glm::vec2 point1, glm::vec2 point2, glm::vec2 point3, float offsetX, float offsetY);
		~TriangleCollider();
	};

}