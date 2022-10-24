#include "stdafx.h"
#include "Particle.h"
#include <ctime>
#include "ParticleEffects.h"
#include "SceneManager.h"
#include "WindowSys.h"

using namespace HARIKEN;

Particle::Particle(particleProperties properties_, glm::vec3 pos, const Scene* gameScene)
{

	setup(properties_, pos, gameScene);

}


Particle::~Particle()
{
	for (auto pframe : img)
		delete pframe;
}

void HARIKEN::Particle::reset(particleProperties properties_, glm::vec3 pos)
{
	
	setup(properties_, pos, currentScene);

}

bool Particle::update(ParticleEffects* effectSpawner, float deltaTime)
{

	effectSpawner->particleUpdate(&properties);
	//Update particle brightness
	if (!kill) {
		if (properties.brightness < 0.0f)
			properties.brightness = 0.0f;
		img[index]->getMeshProperties()->brightness = properties.brightness;
	}
	//Update particle opaqueness
	if (!kill) {
		if (properties.opaqueness < 0.0f)
			properties.opaqueness = 0.0f;
		img[index]->getMeshProperties()->opaqueness = properties.opaqueness;
	}
	//update particle colors
	img[index]->getMeshProperties()->color = properties.color;
	img[index]->getMeshProperties()->lightColor = properties.lightColor;
	//update life timer
	timer += deltaTime;
	//update physics / position
	glm::vec2 temp = u * deltaTime + a * std::powf(deltaTime, 2) / 2.0f;
	v = u + a * deltaTime;

	s = glm::vec3(s.x + temp.x, s.y - temp.y, s.z + properties.z);

	u = v;

	img[index]->setPosition(s);

	float largest = std::fmax(imageSize.x, imageSize.y);
	glm::vec3 tempScale = glm::vec3(1 / largest);
	img[index]->setScale(glm::vec3(tempScale.x * properties.scale.x, tempScale.y * properties.scale.y, tempScale.z));
	//If particle life expired or is killed, initiate kill sequence, slowly fading particle out.
	if (timer >= properties.duration || kill) {

		if (first) {
			wiwawiwi = img[index]->getMeshProperties()->brightness;
			wawawiwa = img[index]->getMeshProperties()->opaqueness;
			first = false;
		}
		kill = true;
		if (properties.fadeOut >= 0.0f) {
			effectSpawner->particleFadeOut(&properties);
			img[index]->getMeshProperties()->brightness -= (deltaTime / properties.fadeOut) * wiwawiwi;
			img[index]->getMeshProperties()->opaqueness -= (deltaTime / properties.fadeOut) * wawawiwa;
		}
		else
			img[index]->getMeshProperties()->opaqueness = 0.0f;

	}
	//Add particle to render queue depending on its depth (2D functionality, 3D to be added)
	if (effectSpawner->renderQueue.empty())
		effectSpawner->renderQueue.push_back(this);

	else {

		bool closest = true;

		for (size_t i = 0; i < effectSpawner->renderQueue.size(); i++) {

			if (s.z <= effectSpawner->renderQueue[i]->getDepth()) {
				effectSpawner->renderQueue.insert(effectSpawner->renderQueue.begin() + static_cast<int>(i), this);
				closest = false;
				break;
			}

		}

		if(closest)
			effectSpawner->renderQueue.push_back(this);

	}

	return true;

}

void Particle::render()
{

	float px = (s.x - currentScene->cameraPos.x) * *Window->positionScale;
	float py = (s.y - currentScene->cameraPos.y) * *Window->positionScale;
	/*
	imagePos.x = std::round((s.x - currentScene->cameraPos.x) * (windowSize.x / 16) - imageSize.x / 2);
	imagePos.y = std::round(windowSize.y - (s.y - currentScene->cameraPos.y) * (windowSize.y / 9) - imageSize.y / 2);

	img[index]->setPosition(glm::vec3(imagePos.x + imageSize.x / 2 - windowSize.x / 2, -(windowSize.y / 2 - (imagePos.y + imageSize.y / 2)), s.z));

	img[index]->render();
	*/
	imagePos.x = std::round(px + windowSize.x / 2);
	imagePos.y = std::round(windowSize.y / 2 - py);

	img[index]->setPosition(glm::vec3(px, -py, 0.0f));

	img[index]->render();

}

bool HARIKEN::Particle::isDead()
{
	//When particle fades out completely, pronounce it dead.
	if (img[index]->getMeshProperties()->opaqueness <= -0.000000000000001) {

		return true;

	}

	return false;
}

float HARIKEN::Particle::getAge()
{
	return timer;
}

float HARIKEN::Particle::getDepth()
{
	return s.z;
}

void HARIKEN::Particle::setup(particleProperties properties_, glm::vec3 pos, const Scene* gameScene)
{
	
	if (once) {
		time = Time::GetInstance();
		Window = WindowSys::GetInstance();
		sceneManager = SceneManager::GetInstance();
		currentScene = gameScene;
		windowSize = Window->getWinSize();
		once = false;
	}
	
	v = glm::vec2();

	timer = 0;
	first = true;
	wiwawiwi = 0;
	wawawiwa = 0;
	kill = false;

	properties = properties_;

	std::string name = properties.particleTexture->name;
	textureID = properties.particleTexture->textureID;

	glm::vec2 imSize = properties.particleTexture->size;
	imageSize.x = imSize.x;
	imageSize.y = imSize.y;

	if (findIndex.find(name.c_str()) == findIndex.end()) {

		img.push_back(new particleFrame(imSize.x, imSize.y, textureID));
		findIndex[name.c_str()] = static_cast<int>(img.size() - 1);
		index = findIndex[name.c_str()];

	}

	else {

		index = findIndex[name.c_str()];

	}

	s = pos;

	if (properties.direction != glm::vec2())
		dir = glm::normalize(properties.direction);
	else
		dir = glm::vec2();

	if (properties.spread > 1)
		properties.spread = 1;
	if (properties.spread < 0)
		properties.spread = 0;

	float largest = std::fmax(imageSize.x, imageSize.y);
	
	glm::vec3 tempScale = glm::vec3(1 / largest);
	img[index]->setScale(glm::vec3(tempScale.x * properties.scale.x, tempScale.y * properties.scale.y, tempScale.z * properties.scale.z));

	float speedX = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / properties.speed));
	float speedY = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / properties.speed));
	dir.x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (properties.spread * 2))) - properties.spread + dir.x;
	dir.y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (properties.spread * 2))) - properties.spread + dir.y;

	if (properties.spawnMode == properties.spawnInFront) {

		properties.z = 0.001;
	}
	if (properties.spawnMode == properties.spawnBehind) {
		properties.z = -0.001;
	}
	if (properties.spawnMode == properties.spawnRandom) {
		properties.z = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.02f))) - 0.01f;
	}

	s.z = s.z + properties.z;

	u.x = dir.x * speedX;
	u.y = dir.y * speedY;

	a = properties.acceleration;

}
