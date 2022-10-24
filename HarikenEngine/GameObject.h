/******************************************************************
GameObject class to be inherited and used as the main building blocks for games.
******************************************************************/

#pragma once
#include <vector>
#include "glew.h"
#include "glm.hpp"
#include "ParticleEffects.h"
#include "Colliders.h"
#include "InputSys.h"
#include "Animation2D.h"
#include "AssetHandler.h"

namespace HARIKEN {

	class Scene;
	class GlobalObjectsHandler;

	class GameObject : public Animation2D
	{

		friend Collision;

	public:
		GameObject();
		GameObject(GameObject* root, GameObject* parent);
		~GameObject();

		virtual void init(Scene* gameScene);
		virtual void onCreate() = 0;
		virtual void update() = 0;
		virtual const void render();
		virtual void Destroy();

		const GameObject* getParent();
		const GameObject* getRoot();

		const glm::vec3 getPos();
		void setPos(float newX, float newY);
		void setPos(float newX, float newY, float newZ);

		glm::vec2 getImagePosition();

		void setScale(glm::vec3 scale_);
		glm::vec3 getScale();

		void afterCreate();
		void passBeforeUpdate();
		void passAfterUpdate();

		void setGravity(bool isTrue);
		void setMass(float weight);

		void addForce(float x, float y);
		void addForce(glm::vec2 vector);

		void setVelocity(float x, float y);
		void setVelocity(glm::vec2 velocity);
		void setVelocity(glm::vec3 velocity);
		glm::vec3 getVelocity();

		void setLinearDamping(float x, float y);
		void setLinearDamping(glm::vec2 vector);
		void setLinearDamping(glm::vec3 vector);

		void addCollider(Collision* newcollider);
		void addTag(std::string);

		bool hasTag(std::string);
		bool isKinematic();

		std::vector<BoundingCollider> modelBound;
		std::vector<Collision*>Colliders;
		std::vector<GameObject*>child;
		std::vector<Model*>model;
		std::vector<ParticleEffects*>particleEffects;

		std::vector<std::string> tag;
		int layer = 0;

		bool isActive = true;
		bool willRender = true;

		Scene* getGameScene();

		AssetFile* getAssetFile(std::string name);

	protected:

		Scene* GameScene;

		void setImg(const Texture* texture);

		std::string pathName;
		std::string p;
		std::string e;

		const Texture* image;

		float width;
		float height;

		float mass = 1;
		bool useGravity = false;

		glm::vec3 velocity = glm::vec3(0.0f);
		glm::vec3 acceleration;
		glm::vec3 linearDamping;

		glm::vec2 imagepos;
		glm::vec3 pos;

		std::vector<GameObject*>collidedObjects;
		glm::vec3 collisionNormal;
		glm::vec2 penetration;

		Time* time;
		InputSys* InputSys;
		WindowSys* Window;
		SceneManager* sceneManager;

		bool kinematic = false;
		/* Functions used for Shaked's assignments
		std::string getMouseState();
		glm::vec2 getMousePosition();
		glm::vec2 getMouseScroll();

		std::vector<glm::vec2>getModelBoxScreenCoord();
		*/
		void addParticleEffect(ParticleEffects* effect);

		bool is3D;

	private:

		friend class Scene;
		friend class GlobalObjectsHandler;
		AssetHandler* assetHandler;

		bool globalObject;

		GameObject* root = nullptr;
		GameObject* parent = nullptr;

		bool created;

		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec2 posCorrection = glm::vec2();
		glm::vec2 disallowVec = glm::vec2(1.0f);
		void updateCollisions();
		void checkCollisions();
		glm::vec3 prevPos;

		std::vector<GameObject*> renderQueue;
		std::vector<ParticleEffects*> particleEffRenderQueue;
		friend void ParticleEffects::afterUpdate(glm::vec3, float);

		std::map<AssetFile*, int> filesUsed;

	};

}