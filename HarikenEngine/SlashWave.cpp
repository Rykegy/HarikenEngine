#include "stdafx.h"
#include "SlashWave.h"

using namespace HARIKEN;

SlashWave::SlashWave()
{

	properties = particleProperties(getAssetFile("PARTICLES")->getTexture("BrilliantEndWave.png"), glm::vec3(1.0f, 0.3f, 0.0f));
	properties.lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	properties.direction = glm::vec2(-1.0f, 0.0f);
	properties.spread = 0.0f;
	properties.speed = 5.0f;
	properties.acceleration = glm::vec2(-5.0f, 0.0f);
	properties.scale = glm::vec3(1280.0f);
	properties.duration = 1000.0f;
	properties.fadeOut = 0.05f;
	properties.brightness = 1.0f;
	properties.opaqueness = 0.01f;
	properties.spawnMode = properties.spawnInFront;

	setFreq(0.001f);
	setMaxParticles(5000);

	stop();

}


SlashWave::~SlashWave()
{
}

void HARIKEN::SlashWave::update()
{
}

void HARIKEN::SlashWave::particleUpdate(particleProperties * properties)
{
}

void HARIKEN::SlashWave::particleFadeOut(particleProperties * properties)
{
}
