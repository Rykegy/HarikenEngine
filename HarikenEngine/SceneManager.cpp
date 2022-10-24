#include "stdafx.h"
#include "SceneManager.h"

using namespace HARIKEN;

std::unique_ptr<SceneManager> SceneManager::instance = nullptr;

SceneManager::SceneManager()
{

}


SceneManager::~SceneManager()
{

}

void HARIKEN::SceneManager::loadScene()
{
	//Load objects in the next scene on an asynchronous thread
	std::future<void> loadFuture = std::async(&SceneManager::loadSceneThread, this, window->newThreadContext());
	std::future<void> shutdownFuture;

	std::vector<std::future<void>*> futures;
	futures.push_back(&loadFuture);
	//Prepare to shut down current scene on another asynchronous thread
	if (currentScene != nullptr) {

		shutdownFuture = std::async(&SceneManager::shutdownSceneThread, this, window->newThreadContext());
		futures.push_back(&shutdownFuture);

	}
	//Throw up loading scene
	loadSomething(&futures);
	//Delete current scene object
	if(currentScene != nullptr)
		delete currentScene;

	currentScene = nextScene;

	for(size_t i = 0; i < scenes.size(); i++)
		if (scenes[i]->getName() == currentScene->getName()) {
			sceneIndex = i;
			break;
		}

	nextScene = nullptr;

	time->reset();

}

void HARIKEN::SceneManager::loadSceneThread(HGLRC threadContext) // Universal start of a new scene loading thread
{

	wglMakeCurrent(window->getHDC(), threadContext);

	nextScene->init();

	wglMakeCurrent(NULL, NULL);

}

void HARIKEN::SceneManager::shutdownSceneThread(HGLRC threadContext) // Universal start of a new shutdown scene thread
{

	wglMakeCurrent(window->getHDC(), threadContext);

	currentScene->shutdown();

	wglMakeCurrent(NULL, NULL);

}

SceneManager * HARIKEN::SceneManager::GetInstance()
{

	if (instance.get() == nullptr)
		instance.reset(new SceneManager);

	return instance.get();

}

bool SceneManager::init()
{

	time = Time::GetInstance();

	window = WindowSys::GetInstance();
	// Create loading scene to be used while loading things
	loading = new loadingScreen();
	loading->init();

	scenes = SCENE_LIST;
	// Load assets required by the game
	std::future<void> future = std::async(&AssetHandler::loadAssetList, AssetHandler::GetInstance(), WindowSys::GetInstance()->newThreadContext());
	std::vector <std::future<void>*> futures;
	
	futures.push_back(&future);
	loadSomething(&futures);

	nextScene = scenes[0]->clone();
	loadScene();

	return false;
}

void SceneManager::update()
{

	if (nextScene != nullptr)
		loadScene();

	if (currentScene != nullptr)
		currentScene->update("HARIKEN");

	time->start();

}

bool SceneManager::shutdown()
{

	if (KMS)
		return true;

	return false;
}

void HARIKEN::SceneManager::loadLevel(std::string name) // Load level by name
{

	std::string key;

	int i = 0;
	while (name[i]) {
		key += tolower(name[i]);
		i++;
	}

	if (key == "next") {
		sceneIndex++;

		if (sceneIndex >= scenes.size()) {

			KMS = true;
			return;

		}

		throwLoadingScreen();
		nextScene = scenes[sceneIndex]->clone();
		currentScene->endScene();
		state = Stay;
		return;

	}

	else if (key == "previous") {

		sceneIndex--;

		if (sceneIndex < 0) {

			KMS = true;
			return;

		}

		throwLoadingScreen();
		nextScene = scenes[sceneIndex]->clone();
		currentScene->endScene();
		state = Stay;
		return;

	}

	else if (key == "exit") {

		currentScene->endScene();
		KMS = true;
		return;

	}

	else {

		for (auto scene : scenes) {

			if (scene->getName() == name) {

				throwLoadingScreen();
				nextScene = scene->clone();
				currentScene->endScene();
				break;

			}

		}

	}
	/*
	if (state != Stay)
		currentScene->KMS = true;
		*/
}

void HARIKEN::SceneManager::loadLevel(Scene * newLevel) // Load level by reference
{

	if (newLevel != nullptr) {

		throwLoadingScreen();
		nextScene = newLevel->clone();
		currentScene->endScene();

	}

	else
		state = Exit;

}

void HARIKEN::SceneManager::loadSomething(std::vector<std::future<void>*>* futures) // Throws loading screen while something loads in a seperate thread
{

	Scene* prev = currentScene;

	loading->startLoading(futures);

	currentScene = loading;

	time->reset();

	while (loading->allThreadsDone != true) {

		time->update();

		currentScene->update("HARIKEN");

		window->render();

		time->start();

	}

	currentScene = prev;

	time->reset();

}

void HARIKEN::SceneManager::setCutInScene(Scene* cutInScene, bool* exitCondition) // Allows cutscenes to be played while in the middle of a scene
{

	Scene* sceneholder = currentScene;
	InputSys* inputSys = InputSys::GetInstance();

	currentScene = nullptr;

	nextScene = cutInScene;
	loadScene();

	time->reset();

	while (*exitCondition != true) {

		time->update();

		inputSys->update();

		currentScene->update("HARIKEN");

		window->render();

		time->start();

	}

	throwLoadingScreen();

	currentScene->shutdown();

	currentScene = sceneholder;

}

void HARIKEN::SceneManager::throwLoadingScreen() // Pre-render the loading screen allowing scene transition to be quickly covered up
{

	Scene* sceneHolder = currentScene;
	currentScene = new loadingScreen;
	time->reset();
	currentScene->update("HARIKEN");
	window->render();
	currentScene = sceneHolder;

}
