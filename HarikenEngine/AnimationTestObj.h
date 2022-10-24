#pragma once
#include "Scene.h"
#include "AfterImageEffect.h"
#include "slashLineEffect.h"

namespace HARIKEN {

	class AnimationTestObj : public GameObject
	{
	public:

		void onCreate();
		void update();

	private:

		AfterImageEffect effect;
		slashLineEffect slashEffect;

		HARIKEN::Animation2DSequence idleAnim;
		HARIKEN::Animation2DSequence attackAnim;
		HARIKEN::Animation2DSequence backJumpAnim;
		HARIKEN::Animation2DSequence landAnim;
		HARIKEN::Animation2DSequence powerUpAnim;

		Sound* gruntSound;
		Sound* attackSound;
		Sound* chargeSound;
		Sound* shortGruntSound;

	};

}