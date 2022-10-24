/**********************************************
A class that holds the data used to display 2D animations.
**********************************************/
#pragma once
#include "Model.h"
#include <vector>
#include "imageFrame.h"
#include "Time.h"
#include "AssetHandler.h"

namespace HARIKEN {

	class Animation2DSequence
	{
	public:
		Animation2DSequence();
		Animation2DSequence(AssetFile* assetFile, std::string animationName, std::string ext, float setFreq);
		virtual ~Animation2DSequence();

		std::string getAnimationName();
		const Texture* getTextureForFrame(int frame);
		Model* getFrame(int frame);
		Model* callLastFrame();
		int getLength();
		float getFreq();

	private:

		AssetFile* assetFile;
		Time* time;

		bool canInterrupt = true;
		std::vector<const Texture*> texture;
		std::vector<Model*> frames;
		float freq;
		std::string name;

	};

}