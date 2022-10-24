/*************
Square Collider.
*************/

#pragma once
#include "Collision.h"

namespace HARIKEN {

	class Collision;
	class SquareCollider : public Collision
	{
	public:
		SquareCollider();
		SquareCollider(float w, float h, float offsetX, float offsetY);
		SquareCollider(float w, float h, glm::vec2 offset);
		~SquareCollider();
	};

}