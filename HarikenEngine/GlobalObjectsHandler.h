/***********************************************************************
Singleton used to store and distribute objects that are meant to be kept accross scenes.
***********************************************************************/

#pragma once
#include "GameObject.h"
#include "UIObject.h"

namespace HARIKEN {

	class GlobalObjectsHandler
	{
	public:

		static GlobalObjectsHandler* GetInstance();

		GlobalObjectsHandler(const GlobalObjectsHandler&) = delete;
		GlobalObjectsHandler(GlobalObjectsHandler&&) = delete;
		GlobalObjectsHandler& operator = (const GlobalObjectsHandler&) = delete;
		GlobalObjectsHandler& operator = (GlobalObjectsHandler&&) = delete;

		void addGameObject(GameObject* gameObject, std::string name);
		GameObject* getGameObject(const std::string& name_);
		std::string getGameObjectKey(const GameObject*);
		void removeGameObjectWithKey(std::string name_);
		void removeGameObject(const GameObject* gameObject);

		void addUIObject(UIObject* uiObject, std::string name_);
		UIObject* getUIObject(const std::string& name_);
		std::string getUIObjectKey(const UIObject*);

	private:

		GlobalObjectsHandler();
		~GlobalObjectsHandler();

		static std::unique_ptr<GlobalObjectsHandler> GlobalObjects;
		friend std::default_delete<GlobalObjectsHandler>;
		friend class SceneManager;

		std::map<std::string, GameObject*>gameObjects = std::map<std::string, GameObject*>();
		std::map<std::string, UIObject*>uiObjects = std::map<std::string, UIObject*>();

	};

}