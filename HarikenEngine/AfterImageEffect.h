/****************************************
Particle effect for creating the after image effect.
****************************************/

#pragma once

#include "ParticleEffects.h"

namespace HARIKEN {

	class AfterImageEffect : public ParticleEffects
	{
	public:
		AfterImageEffect();
		~AfterImageEffect();

		void update();
		void particleUpdate(particleProperties* properties);
		void particleFadeOut(particleProperties* properties);

	};

}