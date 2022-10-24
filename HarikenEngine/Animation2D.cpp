#include "stdafx.h"
#include "Animation2D.h"

using namespace HARIKEN;

Animation2D::~Animation2D()
{
}

Animation2DSequence HARIKEN::Animation2D::createAnimation(AssetFile* assetFile, std::string animationName, std::string ext, float setFreq)
{

	animationHandler->createAnimation(assetFile, animationName, ext, setFreq);

	return getAnimation(animationName);

}

Animation2DSequence Animation2D::getAnimation(std::string animationName)
{

	return *animationHandler->getAnimationSequence(animationName);

}

Animation2DSequence * Animation2D::getCurrentAnim()
{
	return currentAnim;
}

int Animation2D::getCurrentFrame()
{
	return frame;
}

void Animation2D::animPlayOnce(Animation2DSequence * anime)
{

	currentAnim = anime;
	repeat = false;
	animePlay = true;
	frame = 0;
	animTimer = 0;
	animLastFrameReached = false;

}

void Animation2D::animPlayRepeat(Animation2DSequence * anime)
{

	currentAnim = anime;
	repeat = true;
	animePlay = true;
	frame = 0;
	animTimer = 0;
	animLastFrameReached = false;

}

void Animation2D::animPause()
{

	animePlay = false;

}

void Animation2D::animPlay()
{

	animePlay = true;

}

void Animation2D::animStop()
{

	currentAnim = nullptr;

}

void Animation2D::updateSprite(float deltaTime)
{

	if (animTimer >= currentAnim->getFreq()) {

		animTimer = 0;

		if (frame + 1 < currentAnim->getLength())
			frame += 1;

		else if (repeat)
			frame = 0;

		else {
			animLastFrameReached = true;
			animePlay = false;
			animTimer = 0;
		}

	}

	if (animePlay)
		animTimer += deltaTime;

}