/*******************************
Class to be inherited to create a scene
*******************************/

#pragma once
#include <SDL.h>
#include <vector>
#include <string>
#include <SDL_image.h>
#include <glm.hpp>
#include "Model.h"
#include "imageFrame.h"
#include "SkyBox.h"
#include "Time.h"
#include "objLoader.h"
#include "mtlLoader.h"
#include "InputSys.h"
#include "GlobalObjectsHandler.h"

namespace HARIKEN {

	class Collision;
	class SceneManager;
	class InputSys;

	class Scene
	{

	public:

		~Scene();

		virtual void init();
		virtual void update();
		virtual const void render();
		virtual void shutdown();

		virtual Scene* clone() = 0;
		virtual void onCreate() = 0;
		virtual void onStart() = 0;

		virtual std::string getName() = 0;

		float gravity = -9.8f;
		glm::vec2 cameraPos = glm::vec2(0, 0);

		bool twoD = true;

		glm::vec3 bgColor = glm::vec3(0.0f, 0.0f, 0.0f);

		GameObject* findGameObjectWithTag(std::string tag);
		UIObject* findUIObjectWithTag(std::string tag);

		void addObject(GameObject* newObject, std::string name);
		void addUI(UIObject* newUI, std::string name);

	protected:

		WindowSys* windowSys;
		glm::vec2 windowSize;
		Time* time;

		GlobalObjectsHandler* globalObjects;

	private:

		friend class SceneManager;
		friend class Collision;
		friend class GameObject;
		friend class UIObject;
		friend class WindowSys;
		
		void endScene();

		void update(std::string Rikeno);

		friend GameObject::~GameObject();

		void sweepColliders();
		std::vector<GameObject*> renderQueue;
		friend void UIObject::afterUpdate();

		std::vector<UIObject*> UIRenderQueue;
		friend void GameObject::passAfterUpdate();

		//std::vector<SkyBox*>skyBoxes;
		std::vector<GameObject*>objects;
		std::vector<UIObject*>UI;
		std::vector<std::vector<Collision*>>sweepedColliders;

		bool KMS = false;

	};
	// Template for derived scenes to give them a default clone function
	template <typename Derived>
	class derivedScene : public Scene {

		virtual Scene* clone() {

			return new Derived(static_cast<Derived const&> (*this));

		}

	};

}