#include "stdafx.h"
#include "AfterImageEffect.h"
#include "InputSys.h"

using namespace HARIKEN;

AfterImageEffect::AfterImageEffect()
{

	properties.color = glm::vec3(0.5f, 0.0f, 0.0f);
	properties.lightColor = glm::vec3(0.0f, 0.0f, 0.0f);
	properties.direction = glm::vec2(0.0f, 0.0f);
	properties.spread = 1.0f;
	properties.speed = 0.5f;
	properties.acceleration = glm::vec2(0.0f, 0.0f);
	properties.duration = 0.1f;
	properties.fadeOut = 0.25f;
	properties.brightness = 0.8f;
	properties.spawnMode = properties.spawnBehind;
	properties.opaqueness = 0.8;

	setFreq(0.05f);
	setMaxParticles(100);

	stop();

}


AfterImageEffect::~AfterImageEffect()
{
}

void HARIKEN::AfterImageEffect::update()
{
	/*
	if (InputSys::GetInstance()->inputs.onwdown)
		play();

	if (InputSys::GetInstance()->inputs.onwup)
		stop();
	*/
}

void HARIKEN::AfterImageEffect::particleUpdate(particleProperties * properties_)
{

	properties_->scale += glm::vec3(100.0f * deltaTime);

}

void HARIKEN::AfterImageEffect::particleFadeOut(particleProperties * properties)
{
}
