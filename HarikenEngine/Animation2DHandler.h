/*********************************************************
Singleton used to create, store and distribute 2D animation sequences.
*********************************************************/

#pragma once
#include <map>
#include "Animation2DSequence.h"

namespace HARIKEN {

	class Animation2DHandler
	{
	public:

		static Animation2DHandler* GetInstance();

		Animation2DHandler(const Animation2DHandler&) = delete;
		Animation2DHandler(Animation2DHandler&&) = delete;
		Animation2DHandler& operator = (const Animation2DHandler&) = delete;
		Animation2DHandler& operator = (Animation2DHandler&&) = delete;

		void createAnimation(AssetFile* fileName, const std::string animationName, const std::string ext, const float setFreq);
		static const Animation2DSequence* getAnimationSequence(const std::string& AnimationName_);

		static std::map < std::string, Animation2DSequence*> animations;

	private:

		Animation2DHandler();
		virtual ~Animation2DHandler();

		static std::unique_ptr<Animation2DHandler> Animation2DInstance;
		friend std::default_delete<Animation2DHandler>;

	};

}