/***********************************************
Creates a box collider at the maximum limits of the model.
***********************************************/

#pragma once
#include "Model.h"
#include "Collision.h"

namespace HARIKEN {

	class BoundingCollider : public Collision {

	public:
		float minX;
		float minY;
		float minZ;
		float maxX;
		float maxY;
		float maxZ;
		BoundingCollider(Model* m);
		BoundingCollider(Model* m, glm::vec3 offset);
		BoundingCollider(Model* m, glm::vec3 offset, bool is2d);
		~BoundingCollider();

		Model* getModel();

	private:

		Model* model;

	};

}