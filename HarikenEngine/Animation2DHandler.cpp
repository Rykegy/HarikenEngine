#include "stdafx.h"
#include "Animation2DHandler.h"

using namespace HARIKEN;

std::map<std::string, Animation2DSequence*> Animation2DHandler::animations = std::map < std::string, Animation2DSequence*>();
std::unique_ptr<Animation2DHandler> Animation2DHandler::Animation2DInstance = nullptr;

Animation2DHandler::Animation2DHandler()
{
}


Animation2DHandler::~Animation2DHandler()
{
}

Animation2DHandler * HARIKEN::Animation2DHandler::GetInstance()
{

	if (Animation2DInstance.get() == nullptr)
		Animation2DInstance.reset(new Animation2DHandler);

	return Animation2DInstance.get();

}

void HARIKEN::Animation2DHandler::createAnimation(AssetFile* assetFile, const std::string animationName, const std::string ext, const float setFreq)
{

	animations[animationName] = new Animation2DSequence(assetFile, animationName, ext, setFreq);

}

const Animation2DSequence* HARIKEN::Animation2DHandler::getAnimationSequence(const std::string& AnimationName_)
{
	return animations[AnimationName_];
}