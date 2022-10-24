/****************************************************
Class dedicated to calculating, detecting and resolving collisions.
****************************************************/
#pragma once
#include "glm.hpp"
#include <vector>
#include <SDL.h>

namespace HARIKEN {

	class GameObject;
	class SceneManager;
	class Collision
	{
	public:
		Collision();
		~Collision();

		int CIRCLE = 0;
		int SQUARE = 1;
		int CAPSULE = 2;
		int TRIANGLE = 3;
		int BOUNDING = 4;
		int CUSTOM = 5;

		int type = -1;
		bool isTrigger = false;

		bool triggered;

		bool is3D;

		virtual void onCreate(GameObject* owner);
		void update();
		void check();
		bool hasCollided(Collision*);

		glm::vec3 pos;
		std::vector<glm::vec3>points;
		float r;
		GameObject * owner;

	protected:

		glm::vec3 posOffset;
		std::vector<glm::vec3>pointOffsetFromPos;

		glm::vec2 supportXY(glm::vec2 direction, Collision* collider, Collision* otherCollider);
		glm::vec2 supportXZ(glm::vec2 direction, Collision* collider, Collision* otherCollider);
		glm::vec2 supportYZ(glm::vec2 direction, Collision* collider, Collision* otherCollider);

		void EPAXY(std::vector<glm::vec2> simplex, Collision* other);
		void EPAXZ(std::vector<glm::vec2> simplex, Collision* other);
		void EPAYZ(std::vector<glm::vec2> simplex, Collision* other);

	private:

		SceneManager* sceneManager;

	};

}