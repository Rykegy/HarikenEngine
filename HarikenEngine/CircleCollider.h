/**************************************************************
A collider that uses the radial distance around the center to detect collisions.
**************************************************************/

#pragma once
#include "Collision.h"

namespace HARIKEN {

	class CircleCollider : public Collision
	{
	public:
		CircleCollider();
		CircleCollider(float radius, glm::vec2 offset);
		CircleCollider(float radius, float offsetX, float offsetY);
		~CircleCollider();

	};

}