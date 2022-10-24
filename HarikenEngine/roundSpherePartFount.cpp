#include "stdafx.h"
#include "roundSpherePartFount.h"

using namespace HARIKEN;

HARIKEN::roundSpherePartFount::roundSpherePartFount()
{

	properties = particleProperties(getAssetFile("PARTICLES")->getTexture("RoundSoftEdge.png"), glm::vec3(1.0f, 0.3f, 0.0f));
	properties.lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	properties.direction = glm::vec2(0.0f, 0.0f);
	properties.spread = 0.5f;
	properties.speed = 0.5f;
	properties.acceleration = glm::vec2(0.0f, -1.0f);
	properties.scale = glm::vec3(80.0f);
	properties.duration = 0.5f;
	properties.fadeOut = 0.35f;
	properties.brightness = 1.0f;
	properties.opaqueness = 0.01f;
	properties.spawnMode = properties.spawnRandom;
	
	setFreq(0.001f);
	setMaxParticles(5000);
	
}

HARIKEN::roundSpherePartFount::~roundSpherePartFount()
{
}

void HARIKEN::roundSpherePartFount::update()
{

}

void roundSpherePartFount::particleUpdate(particleProperties* properties) {

	properties->brightness -= Time::GetInstance()->deltaTime / 3.5;
	properties->scale += glm::vec3(deltaTime * 200);
	/*
	properties->color.x = std::sin(timer * M_PI / 180);
	properties->color.y = std::sin((timer + 90) * M_PI / 180);
	properties->color.z = std::sin((timer + 180) * M_PI / 180);
	timer += Time::GetInstance()->deltaTime;
	*/
}

void roundSpherePartFount::particleFadeOut(particleProperties* properties) {



}