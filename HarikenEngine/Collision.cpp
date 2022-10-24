#include "stdafx.h"
#include "Collision.h"
#include "SceneManager.h"
#include <limits>
#include "GameObject.h"

using namespace HARIKEN;

Collision::Collision()
{

	type = -1;

}

Collision::~Collision()
{
}

void Collision::onCreate(GameObject * Owner)
{

	sceneManager = SceneManager::GetInstance();

	owner = Owner;
	
	pos = owner->pos + posOffset;

	for (size_t i = 0; i < pointOffsetFromPos.size(); i++) {

		points.push_back(pointOffsetFromPos[i] + pos);

	}

	is3D = owner->is3D;

}

void Collision::update()
{

	pos = owner->pos + posOffset;
			
}

void HARIKEN::Collision::check()
{

	Scene* GameScene = owner->GameScene;

	std::vector<Collision*>possibleCollisions;

	for (size_t i = 0; i < GameScene->sweepedColliders.size(); i++)
		if (!GameScene->sweepedColliders[i].empty()) {
			if (GameScene->sweepedColliders[i].size() > 1 && GameScene->sweepedColliders[i][0] == this) {

				possibleCollisions = GameScene->sweepedColliders[i];

				break;

			}
		}

	for (size_t i = 0; i < pointOffsetFromPos.size(); i++) {

		points[i] = pointOffsetFromPos[i] + pos;

	}

	owner->collidedObjects.clear();
	triggered = false;

	for (size_t i = 1; i < possibleCollisions.size(); i++)
		if (hasCollided(possibleCollisions[i]))
			owner->collidedObjects.push_back(possibleCollisions[i]->owner);

}
//GJK collision detection method, currently handles 2D collisions but can be overhauled to handle 3D.
bool Collision::hasCollided(Collision * other)
{

	int simVertAmount = 0;
	glm::vec2 direction;
	std::vector<glm::vec2> simplex;
	glm::vec2 A;
	glm::vec2 B;
	glm::vec2 C;
	glm::vec2 A0;
	glm::vec2 AB;
	glm::vec2 AC;

	bool loop = true;

	while (loop) { //Search for intersection in XY plane

		switch (simVertAmount) {

		case 0:
			direction = glm::vec2(pos.x, pos.y) - glm::vec2(other->pos.x, other->pos.y);
			simplex.push_back(supportXY(direction, this, other));
			simVertAmount = 1;
			direction = -simplex[0];
			break;

		case 1:
			simplex.push_back(supportXY(direction, this, other));
			simVertAmount = 2;
			if (glm::dot(simplex[1], direction) < 0)
				return false;
			break;

		case 2:
			A = simplex[1];
			B = simplex[0];
			AB = B - A;
			direction = glm::vec2(-AB.y, AB.x);
			if (glm::dot(direction, -A) < 0)
				direction = -direction;
			simplex.push_back(supportXY(direction, this, other));
			simVertAmount = 3;
			if (glm::dot(simplex[2], direction) < 0)
				return false;
			break;

		case 3:
			A = simplex[2];
			B = simplex[1];
			C = simplex[0];
			AB = B - A;
			AC = C - A;
			A0 = -A;
			glm::vec2 ABNorm = glm::vec2(-AB.y, AB.x);
			if (glm::dot(ABNorm, AC) > 0)
				ABNorm = -ABNorm;
			glm::vec2 ACNorm = glm::vec2(-AC.y, AC.x);
			if (glm::dot(ACNorm, AB) > 0)
				ACNorm = -ACNorm;
			if (glm::dot(ABNorm, A0) > 0) {
				direction = ABNorm;
				simplex.clear();
				simplex.push_back(B);
				simplex.push_back(A);
				simplex.push_back(supportXY(direction, this, other));
				if (glm::dot(simplex[2], direction) < 0)
					return false;
				break;
			}
			if (glm::dot(ACNorm, A0) > 0) {
				direction = ACNorm;
				simplex.clear();
				simplex.push_back(C);
				simplex.push_back(A);
				simplex.push_back(supportXY(direction, this, other));
				if (glm::dot(simplex[2], direction) < 0)
					return false;
				break;
			}
			if (glm::dot(-ABNorm, A0) >= 0 && glm::dot(-ACNorm, A0) >= 0) {
				owner->collidedObjects.push_back(other->owner);
				if (isTrigger)
					return false;
				else if (other->isTrigger)
					return false;
				else {
					if (!owner->isKinematic()) {

						EPAXY(simplex, other);

					}

					if (!is3D)
						return true;

					loop = false;
					break;

				}
			}

			return false;
			
		}

	}

	simVertAmount = 0;
	direction = glm::vec2();
	simplex.clear();
	A = glm::vec2();
	B = glm::vec2();
	C = glm::vec2();
	A0 = glm::vec2();
	AB = glm::vec2();
	AC = glm::vec2();

	loop = true;

	while (loop) { //Search for intersection in XZ plane

		switch (simVertAmount) {

		case 0:
			direction = glm::vec2(pos.x, pos.z) - glm::vec2(other->pos.x, other->pos.z);
			simplex.push_back(supportXZ(direction, this, other));
			simVertAmount = 1;
			direction = -simplex[0];
			break;

		case 1:
			simplex.push_back(supportXZ(direction, this, other));
			simVertAmount = 2;
			if (glm::dot(simplex[1], direction) < 0)
				return false;
			break;

		case 2:
			A = simplex[1];
			B = simplex[0];
			AB = B - A;
			direction = glm::vec2(-AB.y, AB.x);
			if (glm::dot(direction, -A) < 0)
				direction = -direction;
			simplex.push_back(supportXZ(direction, this, other));
			simVertAmount = 3;
			if (glm::dot(simplex[2], direction) < 0)
				return false;
			break;

		case 3:
			A = simplex[2];
			B = simplex[1];
			C = simplex[0];
			AB = B - A;
			AC = C - A;
			A0 = -A;
			glm::vec2 ABNorm = glm::vec2(-AB.y, AB.x);
			if (glm::dot(ABNorm, AC) > 0)
				ABNorm = -ABNorm;
			glm::vec2 ACNorm = glm::vec2(-AC.y, AC.x);
			if (glm::dot(ACNorm, AB) > 0)
				ACNorm = -ACNorm;
			if (glm::dot(ABNorm, A0) > 0) {
				direction = ABNorm;
				simplex.clear();
				simplex.push_back(B);
				simplex.push_back(A);
				simplex.push_back(supportXZ(direction, this, other));
				if (glm::dot(simplex[2], direction) < 0)
					return false;
				break;
			}
			if (glm::dot(ACNorm, A0) > 0) {
				direction = ACNorm;
				simplex.clear();
				simplex.push_back(C);
				simplex.push_back(A);
				simplex.push_back(supportXZ(direction, this, other));
				if (glm::dot(simplex[2], direction) < 0)
					return false;
				break;
			}
			if (glm::dot(-ABNorm, A0) >= 0 && glm::dot(-ACNorm, A0) >= 0) {
				owner->collidedObjects.push_back(other->owner);
				if (isTrigger)
					return false;
				else if (other->isTrigger)
					return false;
				else {
					if (!owner->isKinematic()) {

						EPAXZ(simplex, other);

					}

					loop = false;
					break;

				}
			}

			return false;

		}

	}

	simVertAmount = 0;
	direction = glm::vec2();
	simplex.clear();
	A = glm::vec2();
	B = glm::vec2();
	C = glm::vec2();
	A0 = glm::vec2();
	AB = glm::vec2();
	AC = glm::vec2();

	loop = true;

	while (loop) { //Search for intersection in YZ plane

		switch (simVertAmount) {

		case 0:
			direction = glm::vec2(pos.y, pos.z) - glm::vec2(other->pos.y, other->pos.z);
			simplex.push_back(supportYZ(direction, this, other));
			simVertAmount = 1;
			direction = -simplex[0];
			break;

		case 1:
			simplex.push_back(supportYZ(direction, this, other));
			simVertAmount = 2;
			if (glm::dot(simplex[1], direction) < 0)
				return false;
			break;

		case 2:
			A = simplex[1];
			B = simplex[0];
			AB = B - A;
			direction = glm::vec2(-AB.y, AB.x);
			if (glm::dot(direction, -A) < 0)
				direction = -direction;
			simplex.push_back(supportYZ(direction, this, other));
			simVertAmount = 3;
			if (glm::dot(simplex[2], direction) < 0)
				return false;
			break;

		case 3:
			A = simplex[2];
			B = simplex[1];
			C = simplex[0];
			AB = B - A;
			AC = C - A;
			A0 = -A;
			glm::vec2 ABNorm = glm::vec2(-AB.y, AB.x);
			if (glm::dot(ABNorm, AC) > 0)
				ABNorm = -ABNorm;
			glm::vec2 ACNorm = glm::vec2(-AC.y, AC.x);
			if (glm::dot(ACNorm, AB) > 0)
				ACNorm = -ACNorm;
			if (glm::dot(ABNorm, A0) > 0) {
				direction = ABNorm;
				simplex.clear();
				simplex.push_back(B);
				simplex.push_back(A);
				simplex.push_back(supportYZ(direction, this, other));
				if (glm::dot(simplex[2], direction) < 0)
					return false;
				break;
			}
			if (glm::dot(ACNorm, A0) > 0) {
				direction = ACNorm;
				simplex.clear();
				simplex.push_back(C);
				simplex.push_back(A);
				simplex.push_back(supportYZ(direction, this, other));
				if (glm::dot(simplex[2], direction) < 0)
					return false;
				break;
			}
			if (glm::dot(-ABNorm, A0) >= 0 && glm::dot(-ACNorm, A0) >= 0) {
				owner->collidedObjects.push_back(other->owner);
				if (isTrigger)
					return false;
				else if (other->isTrigger)
					return false;
				else {
					if (!owner->isKinematic()) {

						EPAYZ(simplex, other);

					}

					loop = false;
					break;

				}
			}

			return false;

		}

	}
	
	return true;

}
//GJK support function to simplistically create a convex hull using minkowski difference.
glm::vec2 HARIKEN::Collision::supportXY(glm::vec2 direction, Collision * collider, Collision * otherCollider) //XY plane
{

	glm::vec2 maxPoint;
	glm::vec2 maxPointOther;

	if (collider->type == CIRCLE && otherCollider->type == CIRCLE)
		maxPoint = glm::vec2(collider->pos.x, collider->pos.y) + glm::normalize(direction) * collider->r;
	else {

		maxPoint = glm::vec2(collider->points[0].x, collider->points[0].y);
		float maxDot = glm::dot(glm::vec2(collider->points[0].x, collider->points[0].y), direction);

		for (size_t i = 1; i < collider->points.size(); i++) {

			float check = glm::dot(glm::vec2(collider->points[i].x, collider->points[i].y), direction);
			if (check > maxDot) {
				maxPoint = glm::vec2(collider->points[i].x, collider->points[i].y);
				maxDot = check;
			}

		}

	}

	if (collider->type == CIRCLE && otherCollider->type == CIRCLE)
		maxPointOther = glm::vec2(otherCollider->pos.x, otherCollider->pos.y) + glm::normalize(-direction) * otherCollider->r;
	else {

		maxPointOther = glm::vec2(otherCollider->points[0].x, otherCollider->points[0].y);
		float maxDot = glm::dot(glm::vec2(otherCollider->points[0].x, otherCollider->points[0].y), -direction);

		for (size_t i = 1; i < otherCollider->points.size(); i++) {
			//8
			float check = glm::dot(glm::vec2(otherCollider->points[i].x, otherCollider->points[i].y), -direction);
			if (check > maxDot) {
				maxPointOther = glm::vec2(otherCollider->points[i].x, otherCollider->points[i].y);
				maxDot = check;
			}

		}

	}

	return maxPoint - maxPointOther;

}

glm::vec2 HARIKEN::Collision::supportXZ(glm::vec2 direction, Collision* collider, Collision* otherCollider) //XZ plane
{

	glm::vec2 maxPoint;
	glm::vec2 maxPointOther;

	if (collider->type == CIRCLE && otherCollider->type == CIRCLE)
		maxPoint = glm::vec2(collider->pos.x, collider->pos.z) + glm::normalize(direction) * collider->r;
	else {

		maxPoint = glm::vec2(collider->points[0].x, collider->points[0].z);
		float maxDot = glm::dot(glm::vec2(collider->points[0].x, collider->points[0].z), direction);

		for (size_t i = 1; i < collider->points.size(); i++) {

			float check = glm::dot(glm::vec2(collider->points[i].x, collider->points[i].z), direction);
			if (check > maxDot) {
				maxPoint = glm::vec2(collider->points[i].x, collider->points[i].z);
				maxDot = check;
			}

		}

	}

	if (collider->type == CIRCLE && otherCollider->type == CIRCLE)
		maxPointOther = glm::vec2(otherCollider->pos.x, otherCollider->pos.z) + glm::normalize(-direction) * otherCollider->r;
	else {

		maxPointOther = glm::vec2(otherCollider->points[0].x, otherCollider->points[0].z);
		float maxDot = glm::dot(glm::vec2(otherCollider->points[0].x, otherCollider->points[0].z), -direction);

		for (size_t i = 1; i < otherCollider->points.size(); i++) {

			float check = glm::dot(glm::vec2(otherCollider->points[i].x, otherCollider->points[i].z), -direction);
			if (check > maxDot) {
				maxPointOther = glm::vec2(otherCollider->points[i].x, otherCollider->points[i].z);
				maxDot = check;
			}

		}

	}

	return maxPoint - maxPointOther;

}

glm::vec2 HARIKEN::Collision::supportYZ(glm::vec2 direction, Collision* collider, Collision* otherCollider) //YZ plane
{

	glm::vec2 maxPoint;
	glm::vec2 maxPointOther;

	if (collider->type == CIRCLE && otherCollider->type == CIRCLE)
		maxPoint = glm::vec2(collider->pos.y, collider->pos.z) + glm::normalize(direction) * collider->r;
	else {

		maxPoint = glm::vec2(collider->points[0].y, collider->points[0].z);
		float maxDot = glm::dot(glm::vec2(collider->points[0].y, collider->points[0].z), direction);

		for (size_t i = 1; i < collider->points.size(); i++) {

			float check = glm::dot(glm::vec2(collider->points[i].y, collider->points[i].z), direction);
			if (check > maxDot) {
				maxPoint = glm::vec2(collider->points[i].y, collider->points[i].z);
				maxDot = check;
			}

		}

	}

	if (collider->type == CIRCLE && otherCollider->type == CIRCLE)
		maxPointOther = glm::vec2(otherCollider->pos.y, otherCollider->pos.z) + glm::normalize(-direction) * otherCollider->r;
	else {

		maxPointOther = glm::vec2(otherCollider->points[0].y, otherCollider->points[0].z);
		float maxDot = glm::dot(glm::vec2(otherCollider->points[0].y, otherCollider->points[0].z), -direction);

		for (size_t i = 1; i < otherCollider->points.size(); i++) {

			float check = glm::dot(glm::vec2(otherCollider->points[i].y, otherCollider->points[i].z), -direction);
			if (check > maxDot) {
				maxPointOther = glm::vec2(otherCollider->points[i].y, otherCollider->points[i].z);
				maxDot = check;
			}

		}

	}

	return maxPoint - maxPointOther;

}
//Third revision of EPA used for collision resolution.
void HARIKEN::Collision::EPAXY(std::vector<glm::vec2> simplex, Collision* other) //XY Plane
{
	glm::vec2 prevDir = glm::vec2(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
	glm::vec2 prevPrevDir = glm::vec2(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());

	while (true) {
		//Find the edge closest to the origin
		glm::vec2 closestEdge = simplex[0] - simplex[simplex.size() - 1];
		glm::vec2 B = simplex[0];
		glm::vec2 A = simplex[simplex.size() - 1];

		float mindist = glm::length(glm::vec2(A.x * B.y - A.y * B.x)) / glm::length(closestEdge);

		float Aadj = mindist * glm::dot(-A, B - A);

		float index = 0;

		for (size_t i = 1; i < simplex.size(); i++) {

			glm::vec2 edge = simplex[i] - simplex[i - 1];

			glm::vec2 B = simplex[i];
			glm::vec2 A = simplex[i - 1];

			float h = glm::length(glm::vec2(A.x * B.y - A.y * B.x)) / glm::length(edge);

			if (h < mindist) {

				float Aadj = h * glm::dot(-A, B - A);
				mindist = h;
				closestEdge = edge;
				index = i - 1;

			}

		}
		//Find the normal to the edge
		glm::vec2 closestEdgeNormal = glm::vec2(closestEdge.y, -closestEdge.x);
		//Make sure the normal is heading away from the origin
		if (glm::dot(closestEdgeNormal, simplex[index]) < 0)
			closestEdgeNormal = -closestEdgeNormal;
		
		if (closestEdgeNormal.x == 0 && closestEdgeNormal.y == 0) {

			closestEdgeNormal = glm::normalize(glm::vec2(pos.x, pos.y) - glm::vec2(other->pos.x, other->pos.y)) * mindist;

			owner->collisionNormal += glm::vec3(closestEdgeNormal.x, closestEdgeNormal.y, 0.0f);
			return;

		}
		//If the changes in the normal is within tolerance, determine that it is the direction of collision
		float check = glm::length(closestEdgeNormal -prevDir);
		float check2 = glm::length(closestEdgeNormal - prevPrevDir);
		
		if ((check < 0.01 && check >= 0) && (check2 < 0.01 && check2 >=0)) {

			closestEdgeNormal = glm::normalize(closestEdgeNormal) * mindist;

			owner->collisionNormal += glm::vec3(closestEdgeNormal.x, closestEdgeNormal.y, 0.0f);
			return;

		}
		//If not then grow the simplex and recheck to see if there is a closer edge
		prevPrevDir = prevDir;
		prevDir = closestEdgeNormal;

		glm::vec2 newVert = supportXY(closestEdgeNormal, this, other);

		std::vector<glm::vec2>newSimplex;

		for (size_t i = 0; i < simplex.size(); i++) {

			newSimplex.push_back(simplex[i]);

			if (i == index)
				newSimplex.push_back(newVert);

		}

		simplex = newSimplex;

	}

}

void HARIKEN::Collision::EPAXZ(std::vector<glm::vec2> simplex, Collision* other) //XZ Plane
{
	glm::vec2 prevDir = glm::vec2(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
	glm::vec2 prevPrevDir = glm::vec2(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());

	while (true) {
		//Find the edge closest to the origin
		glm::vec2 closestEdge = simplex[0] - simplex[simplex.size() - 1];
		glm::vec2 B = simplex[0];
		glm::vec2 A = simplex[simplex.size() - 1];

		float mindist = glm::length(glm::vec2(A.x * B.y - A.y * B.x)) / glm::length(closestEdge);

		float Aadj = mindist * glm::dot(-A, B - A);

		float index = 0;

		for (size_t i = 1; i < simplex.size(); i++) {

			glm::vec2 edge = simplex[i] - simplex[i - 1];

			glm::vec2 B = simplex[i];
			glm::vec2 A = simplex[i - 1];

			float h = glm::length(glm::vec2(A.x * B.y - A.y * B.x)) / glm::length(edge);

			if (h < mindist) {

				float Aadj = h * glm::dot(-A, B - A);
				mindist = h;
				closestEdge = edge;
				index = i - 1;

			}

		}
		//Find the normal to the edge
		glm::vec2 closestEdgeNormal = glm::vec2(closestEdge.y, -closestEdge.x);
		//Make sure the normal is heading away from the origin
		if (glm::dot(closestEdgeNormal, simplex[index]) < 0)
			closestEdgeNormal = -closestEdgeNormal;

		if (closestEdgeNormal.x == 0 && closestEdgeNormal.y == 0) {

			closestEdgeNormal = glm::normalize(glm::vec2(pos.x, pos.z) - glm::vec2(other->pos.x, other->pos.z)) * mindist;

			owner->collisionNormal += glm::vec3(closestEdgeNormal.x, 0.0f, closestEdgeNormal.y);
			return;

		}
		//If the changes in the normal is within tolerance, determine that it is the direction of collision
		float check = glm::length(closestEdgeNormal - prevDir);
		float check2 = glm::length(closestEdgeNormal - prevPrevDir);

		if ((check < 0.01 && check >= 0) && (check2 < 0.01 && check2 >= 0)) {

			closestEdgeNormal = glm::normalize(closestEdgeNormal) * mindist;

			owner->collisionNormal += glm::vec3(closestEdgeNormal.x, 0.0f, closestEdgeNormal.y);
			return;

		}
		//If not then grow the simplex and recheck to see if there is a closer edge
		prevPrevDir = prevDir;
		prevDir = closestEdgeNormal;

		glm::vec2 newVert = supportXZ(closestEdgeNormal, this, other);

		std::vector<glm::vec2>newSimplex;

		for (size_t i = 0; i < simplex.size(); i++) {

			newSimplex.push_back(simplex[i]);

			if (i == index)
				newSimplex.push_back(newVert);

		}

		simplex = newSimplex;

	}

}

void HARIKEN::Collision::EPAYZ(std::vector<glm::vec2> simplex, Collision* other) //YZ Plane
{
	glm::vec2 prevDir = glm::vec2(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
	glm::vec2 prevPrevDir = glm::vec2(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());

	while (true) {
		//Find the edge closest to the origin
		glm::vec2 closestEdge = simplex[0] - simplex[simplex.size() - 1];
		glm::vec2 B = simplex[0];
		glm::vec2 A = simplex[simplex.size() - 1];

		float mindist = glm::length(glm::vec2(A.x * B.y - A.y * B.x)) / glm::length(closestEdge);

		float Aadj = mindist * glm::dot(-A, B - A);

		float index = 0;

		for (size_t i = 1; i < simplex.size(); i++) {

			glm::vec2 edge = simplex[i] - simplex[i - 1];

			glm::vec2 B = simplex[i];
			glm::vec2 A = simplex[i - 1];

			float h = glm::length(glm::vec2(A.x * B.y - A.y * B.x)) / glm::length(edge);

			if (h < mindist) {

				float Aadj = h * glm::dot(-A, B - A);
				mindist = h;
				closestEdge = edge;
				index = i - 1;

			}

		}
		//Find the normal to the edge
		glm::vec2 closestEdgeNormal = glm::vec2(closestEdge.y, -closestEdge.x);
		//Make sure the normal is heading away from the origin
		if (glm::dot(closestEdgeNormal, simplex[index]) < 0)
			closestEdgeNormal = -closestEdgeNormal;

		if (closestEdgeNormal.x == 0 && closestEdgeNormal.y == 0) {

			closestEdgeNormal = glm::normalize(glm::vec2(pos.y, pos.z) - glm::vec2(other->pos.y, other->pos.z)) * mindist;

			owner->collisionNormal += glm::vec3(0.0f, closestEdgeNormal.x, closestEdgeNormal.y);
			return;

		}
		//If the changes in the normal is within tolerance, determine that it is the direction of collision
		float check = glm::length(closestEdgeNormal - prevDir);
		float check2 = glm::length(closestEdgeNormal - prevPrevDir);

		if ((check < 0.01 && check >= 0) && (check2 < 0.01 && check2 >= 0)) {

			closestEdgeNormal = glm::normalize(closestEdgeNormal) * mindist;

			owner->collisionNormal += glm::vec3(0.0f, closestEdgeNormal.x, closestEdgeNormal.y);
			return;

		}
		//If not then grow the simplex and recheck to see if there is a closer edge
		prevPrevDir = prevDir;
		prevDir = closestEdgeNormal;

		glm::vec2 newVert = supportYZ(closestEdgeNormal, this, other);

		std::vector<glm::vec2>newSimplex;

		for (size_t i = 0; i < simplex.size(); i++) {

			newSimplex.push_back(simplex[i]);

			if (i == index)
				newSimplex.push_back(newVert);

		}

		simplex = newSimplex;

	}

}
