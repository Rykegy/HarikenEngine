#include "stdafx.h"
#include <math.h>
#include<iostream>
#include "GameObject.h"
#include "Time.h"
#include "WindowSys.h"
#include "SceneManager.h"
#include "Colliders.h"

using namespace HARIKEN;

GameObject::GameObject()
{

	pathName = "";

	pos.x = 0;
	pos.y = 0;

	imagepos.x = 0;
	imagepos.y = 0;

	linearDamping.x = 0;
	linearDamping.y = 0;

}

GameObject::GameObject(GameObject * rt, GameObject * pt)
{
	
	root = rt;
	parent = pt;

	pathName = "";

	pos = glm::vec3();

	imagepos.x = 0;
	imagepos.y = 0;

	linearDamping.x = 0;
	linearDamping.y = 0;

}

GameObject::~GameObject()
{

	//Remove itself from the list of objects
	if (parent != nullptr) {

		for (size_t i = 0; i < parent->child.size(); i++)
			if (parent->child[i] == this)
				parent->child.erase(parent->child.begin() + i);

	}

	if (globalObject != true) {

		if (GameScene != nullptr) {

			for (size_t i = 0; i < GameScene->objects.size(); i++)
				if (GameScene->objects[i] == this)
					GameScene->objects.erase(GameScene->objects.begin() + i);

		}



		//Remove GameObject from render queue
		if (parent != nullptr) {

			for (size_t i = 0; i < parent->renderQueue.size(); i++)
				if (parent->renderQueue[i] == this) {

					parent->renderQueue.erase(parent->renderQueue.begin() + i);
					break;

				}

		}

		else if (GameScene != nullptr) {

			for (size_t i = 0; i < GameScene->renderQueue.size(); i++)
				if (GameScene->renderQueue[i] == this) {

					GameScene->renderQueue.erase(GameScene->renderQueue.begin() + i);
					break;

				}

		}

	}

	//Delete objects associated with the Game Objects
	for (auto c : Colliders)
		delete c;
	for (auto g : child)
		delete g;
	if (!globalObject) {
		for (auto m : model) {
			delete m;
		}
	}
	for (auto p : particleEffects)
		delete p;

	for (std::map<AssetFile*, int>::iterator i = filesUsed.begin(); i != filesUsed.end(); i++)
		i->first->disassociate(this);

	filesUsed.clear();

}

void GameObject::init(Scene* gameScene)
{
	//Saves all the pointers to the handlers to improve memory usage when calling them
	time = Time::GetInstance();
	InputSys = InputSys::GetInstance();
	Window = WindowSys::GetInstance();
	sceneManager = SceneManager::GetInstance();
	assetHandler = AssetHandler::GetInstance();

	GameScene = gameScene;

	if (!created) {

		onCreate();
		afterCreate();

	}

}

void HARIKEN::GameObject::onCreate()
{
}

void HARIKEN::GameObject::update()
{
}

const void GameObject::render()
{
	
	glm::vec2 windowSize = Window->getWinSize();
	Scene* currentscene = GameScene;

	//Check for and render any child game objects that should be rendered in front
	while (!renderQueue.empty()) {

		if (renderQueue.back()->layer < layer)
			break;

		renderQueue.back()->render();
		renderQueue.pop_back();

	}

	//Check for any particle effects that should be rendered in front
	while (!particleEffRenderQueue.empty()) {

		if (particleEffRenderQueue.back()->layer < layer)
			break;

		particleEffRenderQueue.back()->render();
		particleEffRenderQueue.pop_back();

	}

	//Render this game object
	//Calculate where this game object is relative to the screen space
	float px = (pos.x - currentscene->cameraPos.x) * *Window->positionScale;
	float py = (pos.y - currentscene->cameraPos.y) * *Window->positionScale;

	//Check if the game object is animated
	if (currentAnim != nullptr) {

		updateSprite(Time::GetInstance()->deltaTime);

		glm::vec2 imgSize = currentAnim->getTextureForFrame(frame)->size;

		imagepos.x = std::round((pos.x - currentscene->cameraPos.x) * (windowSize.x / 16) - imgSize.x / 2);
		
		imagepos.y = std::round(windowSize.y - (pos.y - currentscene->cameraPos.y) * (windowSize.y / 9) - imgSize.y / 2);

		currentAnim->getFrame(frame)->setPosition(glm::vec3(pos.x * *Window->positionScale, -pos.y * *Window->positionScale, 0.0f));
		if (currentAnim->getFrame(frame)->getScale() != scale)
			currentAnim->getFrame(frame)->setScale(glm::vec3(scale));
		currentAnim->getFrame(frame)->render();

	}

	//Check if the game object has an image to be rendered
	else if (image != nullptr) {

		imagepos.x = std::round(px + windowSize.x / 2);
		imagepos.y = std::round(windowSize.y / 2 - py);

		model[0]->setPosition(glm::vec3(px, -py, 0.0f));
		if (model[0]->getScale() != scale)
			model[0]->setScale(glm::vec3(scale));
		model[0]->render();

	}

	//Check if the game has a 3D object to be rendered
	else if (model.size() > 0) {

		for (size_t i = 0; i < model.size(); i++) {

			if (model[i]->getScale() != scale)
				model[i]->setScale(glm::vec3(scale));
			model[i]->render();

		}

	}

	//Check for any particle effects that should be rendered behind
	while (!particleEffRenderQueue.empty()) {

		particleEffRenderQueue.back()->render();
		particleEffRenderQueue.pop_back();

	}

	//Check for any child objects that should be rendered behind
	while (!renderQueue.empty()) {

		renderQueue.back()->render();
		renderQueue.pop_back();

	}

}

void GameObject::Destroy()
{

	

	GameObject::~GameObject();

}

const GameObject * GameObject::getParent()
{
	return parent;
}

const GameObject * GameObject::getRoot()
{
	return root;
}

const glm::vec3 GameObject::getPos()
{
	return pos;
}

void GameObject::setPos(float newX, float newY)
{

	pos = glm::vec3(newX, newY, 0.0f);

}

void HARIKEN::GameObject::setPos(float newX, float newY, float newZ)
{

	pos = glm::vec3(newX, newY, newZ);

}

glm::vec2 HARIKEN::GameObject::getImagePosition()
{
	return imagepos;
}

void HARIKEN::GameObject::setScale(glm::vec3 scale_)
{

	//imgResize(newX, newY);
	scale = scale_;

	for (size_t i = 0; i < model.size(); i++) {
		if (model[i]->getScale() != scale)
			model[i]->setScale(glm::vec3(scale));
	}

}

glm::vec3 HARIKEN::GameObject::getScale()
{

	return scale;

}
//A series of universal things that needs to happen after onCreate
void HARIKEN::GameObject::afterCreate()
{
	for (size_t i = 0; i < Colliders.size(); i++)
		Colliders[i]->onCreate(this);

	for (size_t i = 0; i < child.size(); i++) {
		GameScene->objects.push_back(child[i]);
		child[i]->init(GameScene);
		child[i]->onCreate();
		child[i]->afterCreate();
	}

	for (size_t i = 0; i < particleEffects.size(); i++)
		particleEffects[i]->init(this);

	created = true;

}
//A series of universal things that needs to happen before updates
void GameObject::passBeforeUpdate()
{
	//Various physics calculations
	if (useGravity)
		acceleration.y += GameScene->gravity;
	
	velocity += acceleration * time->deltaTime;

	prevPos = pos;
	pos += velocity * time->deltaTime - acceleration * std::powf(time->deltaTime, 2) / 2.0f;

	if (linearDamping.x != 0 && acceleration.x == 0) {

		velocity.x -= linearDamping.x * time->deltaTime * velocity.x * 5;

		if (velocity.x < 0.05 && velocity.x > -0.05)
			velocity.x = 0;

	}

	if (linearDamping.y != 0 && !useGravity && acceleration.y == 0) {

		velocity.y -= linearDamping.y * time->deltaTime * velocity.y * 5;

		if (velocity.y < 0.05 && velocity.y > -0.05)
			velocity.y = 0;

	}

	acceleration.x = 0;
	acceleration.y = 0;

	for (auto c : child)
		c->passBeforeUpdate();
	
	updateCollisions();

}
//A series of universal things that needs to happen after updates
void HARIKEN::GameObject::passAfterUpdate()
{

	//call update for child objects
	for (auto c : child)
		c->update();

	//call update for particle effects
	for (auto p : particleEffects) {

		p->update();
		p->afterUpdate(glm::vec3(pos.x, pos.y, 0.0f), time->deltaTime);

	}

	//Clear list of collided objects
	collidedObjects.clear();

	//Check for collisions
	collisionNormal = glm::vec3(0.0f);

	checkCollisions();

	if (collisionNormal != glm::vec3(0.0f)) {

		bool velCheckX = false;
		bool velCheckY = false;
		if(collisionNormal.x != 0){
			std::cout << "Good evening" << std::endl;
		}
		setPos(pos.x - collisionNormal.x, pos.y - collisionNormal.y, pos.z - collisionNormal.z);
			
		if (collisionNormal.x > 0 && velocity.x > 0)
			velocity.x = 0;
		if (collisionNormal.x < 0 && velocity.x < 0)
			velocity.x = 0;
		if (collisionNormal.y > 0 && velocity.y > 0)
			velocity.y = 0;
		if (collisionNormal.y < 0 && velocity.y < 0)
			velocity.y = 0;
		if (collisionNormal.z > 0 && velocity.z > 0)
			velocity.z = 0;
		if (collisionNormal.z < 0 && velocity.z < 0)
			velocity.z = 0;

	}

	//Call child after update
	for (auto c : child)
		c->passAfterUpdate();

	//If object needs to be rendered, add it to the render queue according to layer hierarchy
	if (willRender) {

		if (parent != nullptr) {

			if (parent->renderQueue.empty())
				parent->renderQueue.push_back(this);

			else {

				bool closest = true;

				for (size_t i = 0; i < parent->renderQueue.size(); i++) {

					if (layer <= parent->renderQueue[i]->layer) {
						parent->renderQueue.insert(parent->renderQueue.begin() + static_cast<int>(i), this);
						closest = false;
						break;
					}

				}

				if (closest)
					parent->renderQueue.push_back(this);

			}

		}

		else {

			bool closest = true;

			for (size_t i = 0; i < GameScene->renderQueue.size(); i++) {

				if (layer <= GameScene->renderQueue[i]->layer) {
					GameScene->renderQueue.insert(GameScene->renderQueue.begin() + static_cast<int>(i), this);
					closest = false;
					break;
				}

			}

			if (closest)
				GameScene->renderQueue.push_back(this);

		}

	}

}
/* Useless and redundant but keeping it for reference
std::string HARIKEN::GameObject::getMouseState()
{
	std::string data;
	if (InputSys::GetInstance()->inputs.Click.leftclickdown)
		data += "LEFTDOWN";
	else if (InputSys::GetInstance()->inputs.Click.leftclick)
		data += "LEFT";
	if (InputSys::GetInstance()->inputs.Click.rightclickdown)
		data += "RIGHTDOWN";
	else if (InputSys::GetInstance()->inputs.Click.rightclick)
		data += "RIGHT";
	if (InputSys::GetInstance()->inputs.Click.leftclickup)
		data += "LEFTUP";
	if (InputSys::GetInstance()->inputs.Click.rightclickup)
		data += "RIGHTUP";

	return data;
}

glm::vec2 HARIKEN::GameObject::getMousePosition()
{
	return InputSys::GetInstance()->inputs.Click.clickpos;
}

glm::vec2 HARIKEN::GameObject::getMouseScroll()
{
	return InputSys::GetInstance()->inputs.Click.scroll;
}

std::vector<glm::vec2> HARIKEN::GameObject::getModelBoxScreenCoord()
{

	glm::vec2 windowSize = Window->getWinSize();

	float minX = INFINITY;
	float maxX = -INFINITY;
	float minY = INFINITY;
	float maxY = -INFINITY;
	float minZ = INFINITY;
	float maxZ = -INFINITY;

	for (auto m : modelBound) {
		
		glm::mat4 modelView = Camera::GetInstance()->getView() * m.getModel()->getTransform();

		glm::vec3 check = glm::project(glm::vec3(m.minX, m.minY, m.minZ), modelView, Camera::GetInstance()->getPerspective(), glm::vec4(0.0f, 0.0f, windowSize.x, windowSize.y));
		if (check.x < minX && check.x >= 0)
			minX = check.x;
		if (check.x > maxX && check.x >= 0)
			maxX = check.x;
		if (check.y < minY && check.y >= 0)
			minY = check.y;
		if (check.y > maxY && check.y >= 0)
			maxY = check.y;
		if (check.z < minZ)
			minZ = check.z;
		if (check.z > maxZ)
			maxZ = check.z;

		check = glm::project(glm::vec3(m.maxX, m.minY, m.minZ), modelView, Camera::GetInstance()->getPerspective(), glm::vec4(0.0f, 0.0f, windowSize.x, windowSize.y));
		if (check.x < minX && check.x >= 0)
			minX = check.x;
		if (check.x > maxX && check.x >= 0)
			maxX = check.x;
		if (check.y < minY && check.y >= 0)
			minY = check.y;
		if (check.y > maxY && check.y >= 0)
			maxY = check.y;
		if (check.z < minZ)
			minZ = check.z;
		if (check.z > maxZ)
			maxZ = check.z;

		check = glm::project(glm::vec3(m.minX, m.maxY, m.minZ), modelView, Camera::GetInstance()->getPerspective(), glm::vec4(0.0f, 0.0f, windowSize.x, windowSize.y));
		if (check.x < minX && check.x >= 0)
			minX = check.x;
		if (check.x > maxX && check.x >= 0)
			maxX = check.x;
		if (check.y < minY && check.y >= 0)
			minY = check.y;
		if (check.y > maxY && check.y >= 0)
			maxY = check.y;
		if (check.z < minZ)
			minZ = check.z;
		if (check.z > maxZ)
			maxZ = check.z;

		check = glm::project(glm::vec3(m.maxX, m.maxY, m.minZ), modelView, Camera::GetInstance()->getPerspective(), glm::vec4(0.0f, 0.0f, windowSize.x, windowSize.y));
		if (check.x < minX && check.x >= 0)
			minX = check.x;
		if (check.x > maxX && check.x >= 0)
			maxX = check.x;
		if (check.y < minY && check.y >= 0)
			minY = check.y;
		if (check.y > maxY && check.y >= 0)
			maxY = check.y;
		if (check.z < minZ)
			minZ = check.z;
		if (check.z > maxZ)
			maxZ = check.z;

		check = glm::project(glm::vec3(m.minX, m.minY, m.maxZ), modelView, Camera::GetInstance()->getPerspective(), glm::vec4(0.0f, 0.0f, windowSize.x, windowSize.y));
		if (check.x < minX && check.x >= 0)
			minX = check.x;
		if (check.x > maxX && check.x >= 0)
			maxX = check.x;
		if (check.y < minY && check.y >= 0)
			minY = check.y;
		if (check.y > maxY && check.y >= 0)
			maxY = check.y;
		if (check.z < minZ)
			minZ = check.z;
		if (check.z > maxZ)
			maxZ = check.z;

		check = glm::project(glm::vec3(m.maxX, m.minY, m.maxZ), modelView, Camera::GetInstance()->getPerspective(), glm::vec4(0.0f, 0.0f, windowSize.x, windowSize.y));
		if (check.x < minX && check.x >= 0)
			minX = check.x;
		if (check.x > maxX && check.x >= 0)
			maxX = check.x;
		if (check.y < minY && check.y >= 0)
			minY = check.y;
		if (check.y > maxY && check.y >= 0)
			maxY = check.y;
		if (check.z < minZ)
			minZ = check.z;
		if (check.z > maxZ)
			maxZ = check.z;

		check = glm::project(glm::vec3(m.minX, m.maxY, m.maxZ), modelView, Camera::GetInstance()->getPerspective(), glm::vec4(0.0f, 0.0f, windowSize.x, windowSize.y));
		if (check.x < minX && check.x >= 0)
			minX = check.x;
		if (check.x > maxX && check.x >= 0)
			maxX = check.x;
		if (check.y < minY && check.y >= 0)
			minY = check.y;
		if (check.y > maxY && check.y >= 0)
			maxY = check.y;
		if (check.z < minZ)
			minZ = check.z;
		if (check.z > maxZ)
			maxZ = check.z;

		check = glm::project(glm::vec3(m.maxX, m.maxY, m.maxZ), modelView, Camera::GetInstance()->getPerspective(), glm::vec4(0.0f, 0.0f, windowSize.x, windowSize.y));
		if (check.x < minX && check.x >= 0)
			minX = check.x;
		if (check.x > maxX && check.x >= 0)
			maxX = check.x;
		if (check.y < minY && check.y >= 0)
			minY = check.y;
		if (check.y > maxY && check.y >= 0)
			maxY = check.y;
		if (check.z < minZ)
			minZ = check.z;
		if (check.z > maxZ)
			maxZ = check.z;

	}

	std::vector<glm::vec2> returnVec;

	returnVec.push_back(glm::vec2(minX, windowSize.y - maxY));
	returnVec.push_back(glm::vec2(maxX, windowSize.y - minY));
	returnVec.push_back(glm::vec2(minZ, maxZ));

	return returnVec;
}
*/
void HARIKEN::GameObject::addParticleEffect(ParticleEffects * effect)
{

	particleEffects.push_back(effect);

}

void HARIKEN::GameObject::updateCollisions()
{

	if (!Colliders.empty())
		for (size_t i = 0; i < Colliders.size(); i++)
			Colliders[i]->update();

}

void HARIKEN::GameObject::checkCollisions()
{

	if (!Colliders.empty())
		for (size_t i = 0; i < Colliders.size(); i++)
			Colliders[i]->check();

}

void GameObject::setGravity(bool isTrue)
{

	useGravity = isTrue;

}

void GameObject::setMass(float weight)
{

	mass = weight;

}

void GameObject::addForce(float x, float y)
{

	acceleration.x += x / mass;
	acceleration.y += y / mass;

}

void GameObject::addForce(glm::vec2 vector)
{

	acceleration.x += vector.x / mass;
	acceleration.y += vector.y / mass;

}

void GameObject::setVelocity(float x, float y)
{

	velocity.x = x;
	velocity.y = y;

}

void GameObject::setVelocity(glm::vec2 vel)
{

	velocity = glm::vec3(vel.x, vel.y, 0.0f);

}

void HARIKEN::GameObject::setVelocity(glm::vec3 vel)
{

	velocity = vel;

}

glm::vec3 HARIKEN::GameObject::getVelocity()
{
	return velocity;
}

void GameObject::setLinearDamping(float x, float y)
{

	linearDamping = glm::vec3(x, y, 0.0f);

}

void HARIKEN::GameObject::setLinearDamping(glm::vec2 vector)
{

	linearDamping = glm::vec3(vector.x, vector.y, 0.0f);

}

void HARIKEN::GameObject::setLinearDamping(glm::vec3 vector)
{

	linearDamping = vector;

}

void HARIKEN::GameObject::addCollider(Collision * newcollider)
{
	Colliders.push_back(newcollider);
	Colliders[Colliders.size() - 1]->onCreate(this);
}

void HARIKEN::GameObject::addTag(std::string newtag)
{

	tag.push_back(newtag);

}

bool GameObject::hasTag(std::string compare)
{

	if (tag.size() != 0) {

		for (size_t i = 0; i < tag.size(); i++)
			if (tag[i] == compare)
				return true;

	}

	return false;
}

bool HARIKEN::GameObject::isKinematic()
{
	return kinematic;
}

Scene* HARIKEN::GameObject::getGameScene()
{
	return GameScene;
}

AssetFile* HARIKEN::GameObject::getAssetFile(std::string name)
{

	AssetFile* file = assetHandler->getAssetFile(name);

	if (file != nullptr) {

		filesUsed[file] = 0;

		file->associate(this);

		return file;

	}

	return nullptr;

}

void HARIKEN::GameObject::setImg(const Texture* texture)
{

	model.push_back(new imageFrame(texture->size.x, texture->size.y, texture->textureID));
	image = texture;

}

