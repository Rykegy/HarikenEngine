#include "stdafx.h"
#include "GlobalObjectsHandler.h"

using namespace HARIKEN;

std::unique_ptr<GlobalObjectsHandler> GlobalObjectsHandler::GlobalObjects = nullptr;

HARIKEN::GlobalObjectsHandler::GlobalObjectsHandler()
{

}

HARIKEN::GlobalObjectsHandler::~GlobalObjectsHandler()
{
	//
	for (std::map<std::string, GameObject*>::iterator i = gameObjects.begin(); i != gameObjects.end(); i++)
		delete i->second;

	gameObjects.clear();

	for (std::map<std::string, UIObject*>::iterator i = uiObjects.begin(); i != uiObjects.end(); i++)
		delete i->second;

	uiObjects.clear();

}

GlobalObjectsHandler * HARIKEN::GlobalObjectsHandler::GetInstance()
{

	if (GlobalObjects.get() == nullptr)
		GlobalObjects.reset(new GlobalObjectsHandler);

	return GlobalObjects.get();

}

void HARIKEN::GlobalObjectsHandler::addGameObject(GameObject * gameObject_, std::string name_)
{

	if (gameObjects.find(name_) != gameObjects.end())
		return;

	gameObject_->globalObject = true;
	gameObjects[name_] = gameObject_;

}

GameObject * HARIKEN::GlobalObjectsHandler::getGameObject(const std::string & name_)
{

	if (gameObjects.find(name_) == gameObjects.end())
		return nullptr;

	return gameObjects[name_];

}

std::string HARIKEN::GlobalObjectsHandler::getGameObjectKey(const GameObject * gameObject_)
{

	for (std::map<std::string, GameObject*>::iterator i = gameObjects.begin(); i != gameObjects.end(); i++) {

		if (i->second == gameObject_)
			return i->first;

	}

	return "";

}

void HARIKEN::GlobalObjectsHandler::removeGameObjectWithKey(std::string name_)
{

	if (gameObjects.find(name_) == gameObjects.end())
		return;

	gameObjects.erase(name_);

}

void HARIKEN::GlobalObjectsHandler::removeGameObject(const GameObject* gameObject)
{

	for (std::map<std::string, GameObject*>::iterator i = gameObjects.begin(); i != gameObjects.end(); i++) {

		if (i->second == gameObject) {
			gameObjects.erase(i);
			return;
		}

	}

}

void HARIKEN::GlobalObjectsHandler::addUIObject(UIObject * uiObject, std::string name_)
{

	if (uiObjects.find(name_) != uiObjects.end())
		return;

	uiObjects[name_] = uiObject;

}

UIObject * HARIKEN::GlobalObjectsHandler::getUIObject(const std::string & name_)
{

	if (uiObjects.find(name_) == uiObjects.end())
		return nullptr;

	return uiObjects[name_];

}

std::string HARIKEN::GlobalObjectsHandler::getUIObjectKey(const UIObject * uiObject_)
{

	for (std::map<std::string, UIObject*>::iterator i = uiObjects.begin(); i != uiObjects.end(); i++) {

		if (i->second == uiObject_)
			return i->first;

	}

	return "";

}
