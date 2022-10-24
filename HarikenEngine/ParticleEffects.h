/******************************************************
Class used for spawning and controlling the behaviour of particles.
******************************************************/

#pragma once

#include <vector>
#include "Particle.h"
#include "Time.h"
#include <queue>

namespace HARIKEN {

#define MAX_PARTICLES (1024 * 1024)

	struct ssbo_data {

		particleProperties properties;
		Particle particles[MAX_PARTICLES];

	};
	
	class GameObject;
	class ParticleEffects
	{
	public:
		ParticleEffects();
		~ParticleEffects();

		virtual void update() = 0;
		virtual void particleUpdate(particleProperties* properties) = 0;
		virtual void particleFadeOut(particleProperties* properties) = 0;

		void init(GameObject* owner_);
		void afterUpdate(glm::vec3 pos, float deltaTime_);
		void render();

		void play();
		void stop();

		float layer = 0;

		particleProperties* getParticleProperties();
		void setPos(glm::vec3);
		glm::vec3 getPos();

		AssetFile* getAssetFile(std::string name);

	protected:

		float deltaTime;

		void setFreq(float frequency);
		void setMaxParticles(int maxNum);

		void drawLine(std::vector<glm::vec2>lineKeyPoint, int density);

		particleProperties properties;
		AssetHandler* assetHandler;

	private:

		void spawnParticle(glm::vec3 position);

		std::vector<Particle*> emittedParticles;
		std::queue<Particle*> resetParticles;
		std::vector<Particle*> renderQueue;
		friend bool Particle::update(ParticleEffects*, float);

		std::vector<glm::vec3> linePoints;

		glm::vec3 s = glm::vec3();
		float frequency = 1.0f;
		float timer = 0.0f;

		int maxPart = 500;
		int lineDownIndex = 0;
		int lineUpIndex = 0;
		int lineMidUpIndex = 0;
		int lineMidDownIndex = 0;

		bool first = true;

		bool isPlaying = true;

		bool lineDrawn = false;

		GameObject* owner;

		//compute shader stuff
		GLuint ssbo;
		GLuint particleLoc;

		Particle* ssbo_particle_dataLoc;

	};

}