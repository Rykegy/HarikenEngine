/**************************************************
Class designed to be used to control 2D animation sequences.
**************************************************/

#pragma once
#include "Animation2DHandler.h"

namespace HARIKEN {

	class Animation2D
	{
	public:
		virtual ~Animation2D();

	protected:

		Animation2DHandler* animationHandler = Animation2DHandler::GetInstance();
		Animation2DSequence createAnimation(AssetFile* assetFile, std::string animationName, std::string ext, float setFreq);

		Animation2DSequence getAnimation(std::string animationName);
		void animPlayOnce(Animation2DSequence* anime);
		void animPlayRepeat(Animation2DSequence* anime);
		void animPause();
		void animPlay();
		void animStop();
		void updateSprite(float deltaTime);
		float animTimer = 0;
		bool animePlay = false;
		bool animLastFrameReached;

		int frame = 0;
		bool repeat = true;

		Animation2DSequence* getCurrentAnim();
		int getCurrentFrame();

	private:

		std::vector<Animation2DSequence> animations;
		Animation2DSequence* currentAnim;
		friend class GameObject;

	};

}