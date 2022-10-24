/************************************
A particle effect that creates a fireball effect.
************************************/

#pragma once

#include "ParticleEffects.h"

namespace HARIKEN {

	class roundSpherePartFount : public ParticleEffects
	{
	public:

		roundSpherePartFount();
		~roundSpherePartFount();

		void update();
		void particleUpdate(particleProperties* properties);
		void particleFadeOut(particleProperties* properties);

	private:

		float timer = 0.0f;

	};

}