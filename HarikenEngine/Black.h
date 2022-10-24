/******************
Protagonist unit data.
******************/

#pragma once
#include "Unit.h"
#include "AfterImageEffect.h"
#include "SlashWave.h"

namespace MEIUN {

	class Black : public derivedUnit<Black>
	{
	public:

		void onCreate();
		void update();

		void Attack();

	private:

		bool slashing = false;
		bool backJump = false;
		bool landing = false;

		HARIKEN::AfterImageEffect* afterImageEffect;
		HARIKEN::SlashWave* slashWaveEffect;

		float timer = 0.0f;
		float techTimer = 0.0f;

		HARIKEN::Sound* Grunt;
		HARIKEN::Sound* Charge;
		HARIKEN::Sound* LongGrunt;
		HARIKEN::Sound* ShortGrunt;
		HARIKEN::Sound* SharpGrunt;

		HARIKEN::Animation2DSequence* powerUp;
		HARIKEN::Animation2DSequence* brilliantEndAnim;

	};

}