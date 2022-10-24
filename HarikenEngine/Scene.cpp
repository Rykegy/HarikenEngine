#include "stdafx.h"
#include "Scene.h"
#include "Colliders.h"

using namespace HARIKEN;

HARIKEN::Scene::~Scene()
{

	shutdown();

}

void Scene::init()
{

	KMS = false;

	windowSys = WindowSys::GetInstance();
	windowSize = windowSys->getWinSize();

	globalObjects = GlobalObjectsHandler::GetInstance();

	time = Time::GetInstance();

	onCreate();

	onStart();

	Time::GetInstance()->reset();

}

void HARIKEN::Scene::update()
{

	//Inherited update loop

}

void HARIKEN::Scene::endScene()
{

	KMS = true;

}

void Scene::update(std::string Rikeno)
{

	if (Rikeno != "HARIKEN")
		return;

	if (objects.size() > 0) {

		for (size_t i = 0; i < objects.size(); i++) {

			if (objects[i]->isActive)
				objects[i]->passBeforeUpdate();
				objects[i]->update();

			if (KMS)
				return;

		}

		sweepColliders();

		for (size_t i = 0; i < objects.size(); i++) {

			if (objects[i]->isActive)
				objects[i]->passAfterUpdate();

		}

	}

	for (size_t i = 0; i < UI.size(); i++) {

		if (UI[i]->isActive) {

			if (UI[i]->request.requestMade)
				UI[i]->realSetText();

			UI[i]->update();
			UI[i]->afterUpdate();

			if (KMS)
				return;

		}

	}

	update();

}

const void Scene::render()
{
	/*
	for (auto s : skyBoxes)
		s->render();
		*/
	if (twoD) {

		while (!renderQueue.empty()) {

			renderQueue.back()->render();
			renderQueue.pop_back();

		}

	}

	else {
		for (size_t i = 0; i < objects.size(); i++) {

			if (objects[i]->isActive)
				objects[i]->render();

		}
	}

	while (!UIRenderQueue.empty()) {

		UIRenderQueue.back()->render();
		UIRenderQueue.pop_back();

	}

}

void Scene::shutdown()
{

	KMS = false;
	cameraPos = glm::vec2(0, 0);

	std::vector<GameObject*>DeleteObject;
	for (size_t i = 0; i < objects.size(); i++) {
		if(globalObjects->getGameObjectKey(objects[i]) == "")
			DeleteObject.push_back(objects[i]);
	}
	for (auto o : DeleteObject)
		delete o;

	objects.clear();

	for (size_t i = 0; i < UI.size(); i++)
		delete UI[i];

	UI.clear();

	renderQueue.clear();

}

GameObject * HARIKEN::Scene::findGameObjectWithTag(std::string tag)
{

	for (auto o : objects) {

		if (o->hasTag(tag))
			return o;

	}

	return nullptr;
}

UIObject * HARIKEN::Scene::findUIObjectWithTag(std::string tag)
{

	for (auto u : UI) {

		if (u->hasTag(tag))
			return u;

	}

	return nullptr;

}

void HARIKEN::Scene::addObject(GameObject * newObject, std::string name)
{

	for (auto o : objects)
		if (o == newObject)
			return;

	objects.push_back(newObject);
	objects[objects.size() - 1]->addTag(name);

	newObject->init(this);

}

void HARIKEN::Scene::addUI(UIObject * newUI, std::string name)
{

	for (auto u : UI)
		if (u == newUI)
			return;

	UI.push_back(newUI);
	UI[UI.size() - 1]->addTag(name);

	newUI->init(this);

}

void HARIKEN::Scene::sweepColliders()
{

	std::vector<Collision*>allColliders;
	sweepedColliders.clear();

	for (size_t i = 0; i < objects.size(); i++) // Start of AABB overlap test
		for (size_t j = 0; j < objects[i]->Colliders.size(); j++)
			allColliders.push_back(objects[i]->Colliders[j]);

	for (size_t i = 0; i < allColliders.size(); i++) { //Perform sweep

		sweepedColliders.push_back(std::vector<Collision*>());

		sweepedColliders[i].push_back(allColliders[i]);

		float minXi;
		float maxXi;
		float minYi;
		float maxYi;

		if (allColliders[i]->type == 0) {
			minXi = allColliders[i]->pos.x - allColliders[i]->r;
			maxXi = allColliders[i]->pos.x + allColliders[i]->r;
			minYi = allColliders[i]->pos.y - allColliders[i]->r;
			maxYi = allColliders[i]->pos.y + allColliders[i]->r;
		}

		else {

			minXi = allColliders[i]->points[0].x;
			maxXi = minXi;
			minYi = allColliders[i]->points[0].y;
			maxYi = minYi;

			for (size_t k = 1; k < allColliders[i]->points.size(); k++) {

				if (allColliders[i]->points[k].x < minXi)
					minXi = allColliders[i]->points[k].x;
				if (allColliders[i]->points[k].x > maxXi)
					maxXi = allColliders[i]->points[k].x;
				if (allColliders[i]->points[k].y < minYi)
					minYi = allColliders[i]->points[k].y;
				if (allColliders[i]->points[k].y > maxYi)
					maxYi = allColliders[i]->points[k].y;

			}
		}

		minXi -= glm::length(allColliders[i]->owner->getVelocity()) * Time::GetInstance()->deltaTime;
		maxXi += glm::length(allColliders[i]->owner->getVelocity()) * Time::GetInstance()->deltaTime;
		minYi -= glm::length(allColliders[i]->owner->getVelocity()) * Time::GetInstance()->deltaTime;
		maxYi += glm::length(allColliders[i]->owner->getVelocity()) * Time::GetInstance()->deltaTime;

		for (size_t j = 0; j < allColliders.size(); j++) {

			if (i != j) {

				float minXj;
				float maxXj;
				float minYj;
				float maxYj;

				if (allColliders[j]->type == 0) {
					minXj = allColliders[j]->pos.x - allColliders[j]->r;
					maxXj = allColliders[j]->pos.x + allColliders[j]->r;
					minYj = allColliders[j]->pos.y - allColliders[j]->r;
					maxYj = allColliders[j]->pos.y + allColliders[j]->r;
				}

				else {

					minXj = allColliders[j]->points[0].x;
					maxXj = minXj;
					minYj = allColliders[j]->points[0].y;
					maxYj = minYj;

					for (size_t k = 1; k < allColliders[j]->points.size(); k++) {

						if (allColliders[j]->points[k].x < minXj)
							minXj = allColliders[j]->points[k].x;
						if (allColliders[j]->points[k].x > maxXj)
							maxXj = allColliders[j]->points[k].x;
						if (allColliders[j]->points[k].y < minYj)
							minYj = allColliders[j]->points[k].y;
						if (allColliders[j]->points[k].y > maxYj)
							maxYj = allColliders[j]->points[k].y;

					}

				}

				minXj -= glm::length(allColliders[j]->owner->getVelocity()) * Time::GetInstance()->deltaTime;
				maxXj += glm::length(allColliders[j]->owner->getVelocity()) * Time::GetInstance()->deltaTime;
				minYi -= glm::length(allColliders[j]->owner->getVelocity()) * Time::GetInstance()->deltaTime;
				maxYj += glm::length(allColliders[j]->owner->getVelocity()) * Time::GetInstance()->deltaTime;

				if ((minXj >= minXi && minXj <= maxXi) || (maxXj >= minXi && maxXj <= maxXi) || (minXi >= minXj && minXi <= maxXj) || (maxXi >= minXj && maxXi <= maxXj))
					if ((minYj >= minYi && minYj <= maxYi) || (maxYj >= minYi && maxYj <= maxYi) || (minYi >= minYj && minYi <= maxYj) || (maxYi >= minYj && maxYi <= maxYj)) {

						sweepedColliders[i].push_back(allColliders[j]);

					}

			}

		}

	}

}