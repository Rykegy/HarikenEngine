#include "stdafx.h"
#include "respawner.h"


namespace HARIKEN {

	void respawner::update() {

		for (size_t i = 0; i < collidedObjects.size(); i++) {

			if (collidedObjects[i]->hasTag("Player")) {

				collidedObjects[i]->setPos(8, 2);

			}

		}

	}

}