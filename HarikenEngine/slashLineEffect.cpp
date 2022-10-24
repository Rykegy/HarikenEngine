#include "stdafx.h"
#include "slashLineEffect.h"


slashLineEffect::slashLineEffect()
{

	properties = particleProperties(getAssetFile("PARTICLES")->getTexture("RoundSoftEdge.png"));
	properties.color = glm::vec3(0.0f, 0.2f, 1.0f);
	properties.lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	properties.direction = glm::vec2(0.0f, 0.0f);
	properties.spread = 1.0f;
	properties.speed = 1.0f;
	properties.acceleration = glm::vec2(0.0f, 0.0f);
	properties.duration = 0.5f;
	properties.fadeOut = 0.25f;
	properties.brightness = 0.8f;
	properties.spawnMode = properties.spawnInFront;
	properties.opaqueness = 0.8;
	properties.scale = glm::vec3(20.0f);

	setFreq(0.0005f);
	setMaxParticles(5000);

	std::vector<glm::vec2> points;
	points.push_back(glm::vec2(2.0f, 7.0f));
	points.push_back(glm::vec2(2.0f, 3.0f));
	points.push_back(glm::vec2(6.0f, 3.0f));
	points.push_back(glm::vec2(6.0f, 7.0f));
	points.push_back(glm::vec2(2.0f, 7.0f));

	drawLine(points, 200);

}


slashLineEffect::~slashLineEffect()
{
}

void slashLineEffect::update()
{

}

void slashLineEffect::particleUpdate(particleProperties * properties)
{
}

void slashLineEffect::particleFadeOut(particleProperties * properties)
{
}
