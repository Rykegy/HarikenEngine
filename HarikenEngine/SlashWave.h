/*********************************************
Particle effect used to create a sword slash beam thing.
*********************************************/

#pragma once

namespace HARIKEN {

	class SlashWave : public ParticleEffects
	{
	public:

		SlashWave();
		~SlashWave();

		void update();
		void particleUpdate(particleProperties* properties);
		void particleFadeOut(particleProperties* properties);

	private:

		float timer = 0.0f;

	};

}