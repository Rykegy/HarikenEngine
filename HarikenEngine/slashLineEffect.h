/*************************
Unused shaped particle effect.
*************************/

#pragma once
#include "ParticleEffects.h"

using namespace HARIKEN;

class slashLineEffect : public ParticleEffects
{
public:
	slashLineEffect();
	~slashLineEffect();

	void update();
	void particleUpdate(particleProperties* properties);
	void particleFadeOut(particleProperties* properties);

};

