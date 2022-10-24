/***************************************************************************************
Singleton to handle transition between scenes and handles their creation and is in charge of updating them
***************************************************************************************/

#pragma once
#include <vector>
#include <glm.hpp>
#include <glm.hpp>
#include <cctype>
#include <locale>
#include <future>
#include "Scene.h"
#include <memory>
#include "Time.h"
#include "loadingScreen.h"
#include "SCENE_LIST.h"

namespace HARIKEN {

	class SceneManager
	{
	public:

		SceneManager(const SceneManager&) = delete;
		SceneManager(SceneManager&&) = delete;
		SceneManager& operator = (const SceneManager&) = delete;
		SceneManager& operator = (SceneManager&&) = delete;

		static SceneManager* GetInstance();

		bool init();
		void update();
		bool shutdown();

		void loadLevel(std::string name);
		void loadLevel(Scene* newLevel);
		void loadSomething(std::vector<std::future<void>*>* future);

		void setCutInScene(Scene* cutInScene, bool* exitCondition);

		void throwLoadingScreen();

	protected:
		int sceneIndex = 0;
		std::vector<Scene*> scenes;

		bool KMS = false;

	private:

		enum sceneSwitchState {

			Stay,
			Previous,
			Next,
			Swap,
			Exit,

		};

		SceneManager();
		~SceneManager();

		static std::unique_ptr<SceneManager>instance;
		friend std::default_delete<SceneManager>;

		sceneSwitchState state = Stay;

		loadingScreen* loading;

	private:

		Time* time;

		WindowSys* window;

	private:

		friend class loadingScreen;
		friend class Mesh;

		void loadScene();
		void loadSceneThread(HGLRC threadContext);
		void shutdownSceneThread(HGLRC threadContext);

		std::vector<Mesh*> readyMesh;

	private:

		friend class SceneManager;
		friend class WindowSys;

		Scene* currentScene = nullptr;
		Scene* nextScene = nullptr;

	};

}