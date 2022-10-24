#include "stdafx.h"
#include "Animation2DSequence.h"

using namespace HARIKEN;

HARIKEN::Animation2DSequence::Animation2DSequence() // Default constructor, creates an empty 2D animation
{

	assetFile = nullptr;
	time = Time::GetInstance();

	freq = 0;
	name = "Invalid Animation";

}

Animation2DSequence::Animation2DSequence(AssetFile* assetFile_, std::string animationName, std::string ext, float setFreq) // Proper constructor, creating an ordered list of textures to be used for a 2D animation sequence. Files must be named after the animation with a frame number following it starting with 0.
{

	assetFile = assetFile_;
	time = Time::GetInstance();

	name = animationName;
	std::string e = ext;

	freq = setFreq;

	if (e != "") {

		for(int i = 0; i < assetFile->getTextureAmount(); i++) { // Searches through the entire asset file for all the textures with the name of the animation starting with frame 0 and ends when it is unable to find a texture with the next incremented frame number.

			std::string temp = name + std::to_string(i) + '.' + e;

			const Texture* tempTexture = assetFile->getTexture(temp);
			if (tempTexture == nullptr)
				break;

			frames.push_back(new imageFrame(tempTexture->size.x, tempTexture->size.y, tempTexture->textureID));
			texture.push_back(tempTexture);

		}

	}

}


Animation2DSequence::~Animation2DSequence()
{
}

std::string HARIKEN::Animation2DSequence::getAnimationName()
{
	return name;
}

const Texture* Animation2DSequence::getTextureForFrame(int frame)
{
	return texture[frame];
}

Model * HARIKEN::Animation2DSequence::getFrame(int frame)
{
	return frames[frame];
}

Model * HARIKEN::Animation2DSequence::callLastFrame()
{
	return frames[frames.size()];
}

int HARIKEN::Animation2DSequence::getLength()
{
	return frames.size();
}

float HARIKEN::Animation2DSequence::getFreq()
{
	return freq;
}
