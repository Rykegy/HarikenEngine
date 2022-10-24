/*******************************************************
Particle class, to be spawned and controlled by particle effects class.
*******************************************************/

#pragma once
#include <glew.h>
#include <string>
#include "glm.hpp"
#include "Time.h"
#include "particleFrame.h"
#include "imageFrame.h"
#include "AssetHandler.h"

namespace HARIKEN {

	struct particleProperties {

		const Texture* particleTexture = nullptr;
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
		float duration = 10.0f;
		float speed = 1.0f;
		glm::vec2 acceleration = glm::vec2();
		float brightness = 1.0f;
		float opaqueness = 1.0f;
		glm::vec2 direction = glm::vec2();
		float spread = 0;
		glm::vec3 scale = glm::vec3(1.0f);
		float fadeOut = 1.0f;
		float z = 0.0f;

		enum SpawnMode { spawnInFront, spawnBehind, spawnRandom };

		SpawnMode spawnMode = spawnBehind;

		particleProperties() {}

		particleProperties(const Texture* texture) {

			particleTexture = texture;

		}

		particleProperties(const Texture* texture, glm::vec3 color_){

			particleTexture = texture;
			color = color_;

		}

	};

	class ParticleEffects;
	class SceneManager;
	class WindowSys;
	class Scene;

	class Particle
	{

	public:
		Particle(particleProperties properties, glm::vec3 pos, const Scene* gameScene);
		~Particle();

		void reset(particleProperties properties, glm::vec3 pos);

		bool update(ParticleEffects* effectSpawner, float deltaTime);
		void render();

		bool isDead();
		float getAge();
		float getDepth();

		bool kill = false;

	private:

		void setup(particleProperties properties, glm::vec3 pos, const Scene* gameScene);

		GLuint textureID;

		glm::vec2 u = glm::vec2();
		glm::vec2 v = glm::vec2();
		glm::vec2 a = glm::vec2();
		glm::vec3 s = glm::vec3();
		glm::vec2 dir = glm::vec2();

		std::vector<Model*> img;

		std::map < std::string, int> findIndex;

		float timer = 0;
		bool first = true;
		float wiwawiwi = 0;
		float wawawiwa = 0;
		particleProperties properties;

		int index = -1;
		
		glm::vec2 imagePos = glm::vec2(1.0f);

		bool once = true;

		Time* time;
		WindowSys* Window;
		SceneManager* sceneManager;

		const Scene* currentScene;
		glm::vec2 windowSize;
		glm::vec2 imageSize;
		
	};

}