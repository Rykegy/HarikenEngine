#include "stdafx.h"
#include "AnimationTestObj.h"
#include "Time.h"

using namespace HARIKEN;
float startScale;
float endScale;
bool shrink = true;
float scaleFactor = 0;

bool slashing = false;
bool backJump = false;
bool landing = false;
bool powering = false;

void HARIKEN::AnimationTestObj::onCreate()
{
	//createAnimation("SaitoSketchAnimation", "jpg", 0.5f, "SaitoDraw");
	//createAnimation("Noel", "jpg", 0.5f, "NoelDraw");
	idleAnim = createAnimation(getAssetFile("BLKANIM"), "Idle", "png", 0.1f);
	attackAnim = createAnimation(getAssetFile("BLKANIM"), "Attack", "png", 0.05f);
	backJumpAnim = createAnimation(getAssetFile("BLKANIM"), "BackJump", "png", 0.05f);
	landAnim = createAnimation(getAssetFile("BLKANIM"), "Land", "png", 0.01f);
	powerUpAnim = createAnimation(getAssetFile("BLKANIM"), "PowerUp", "png", 0.1f);

	animPlayRepeat(&idleAnim);

	effect.layer = layer + 1;
	//slashEffect.layer = layer - 1;

	particleEffects.push_back(&effect);
	//particleEffects.push_back(&slashEffect);

	shortGruntSound = getAssetFile("BLKETC")->getSound("BlkShortGrunt0.wav");
	attackSound = getAssetFile("BLKETC")->getSound("BlkSharpGrunt.wav");
	chargeSound = getAssetFile("BLKETC")->getSound("BlkCharge.wav");
	gruntSound = getAssetFile("BLKETC")->getSound("BlkGrunt1.wav");
	/*
	glm::vec3 scale;
	
	if (TextureHandler::GetInstance()->getTextureData(getAnimation("SaitoDraw")->getImageKeyForFrame(0))->height > windowSize.y || TextureHandler::GetInstance()->getTextureData(getAnimation("SaitoDraw")->getImageKeyForFrame(0))->width > windowSize.y) {

		if (TextureHandler::GetInstance()->getTextureData(getAnimation("SaitoDraw")->getImageKeyForFrame(0))->height - windowSize.y > TextureHandler::GetInstance()->getTextureData(getAnimation("SaitoDraw")->getImageKeyForFrame(0))->width - windowSize.x) {

			scale.x = windowSize.y / TextureHandler::GetInstance()->getTextureData(getAnimation("SaitoDraw")->getImageKeyForFrame(0))->height;
			scale.y = scale.x;

		}

		else {

			scale.x = windowSize.x / TextureHandler::GetInstance()->getTextureData(getAnimation("SaitoDraw")->getImageKeyForFrame(0))->width;
			scale.y = scale.x;

		}

		setScale(scale);

	}
	*/
	//setPos(16 - (16 / windowSize.x) * (TextureHandler::GetInstance()->getTextureData(getAnimation("SaitoDraw")->getImageKeyForFrame(0))->width * scale.x / 2), 4.5);
	setPos(0, 0);
	//setScale(glm::vec3(1.5, 1.5, -1));
	//startScale = scale.x;
	//endScale = scale.x * 0.5f;

}

void HARIKEN::AnimationTestObj::update()
{
	//std::cout << getCurrentAnim()->getFrame(getCurrentFrame())->getPosition().x << ", " << getCurrentAnim()->getFrame(getCurrentFrame())->getPosition().y << std::endl;
	
	effect.setPos(getCurrentAnim()->getFrame(getCurrentFrame())->getPosition());
	effect.getParticleProperties()->particleTexture = getCurrentAnim()->getTextureForFrame(getCurrentFrame());
	float maxImageSize = std::fmax(effect.getParticleProperties()->particleTexture->size.x, effect.getParticleProperties()->particleTexture->size.y);
	effect.getParticleProperties()->scale = getScale() * maxImageSize;

	//glm::vec3 s = static_cast<imageFrame*>(getCurrentAnim()->getFrame(getCurrentFrame()))->getSize();

	//std::cout << s.x << "," << s.y << std::endl;
	
	if (InputSys::GetInstance()->inputs.onpdown && !powering && !slashing) {

		animPlayOnce(&powerUpAnim);
		powering = true;

	}

	if (powering) {

		if (getCurrentFrame() == 0) {

			if (!chargeSound->isPlaying())
				chargeSound->play();

		}

		if (getCurrentFrame() == 3) {
			effect.play();
		}

		if (animLastFrameReached) {
			powering = false;
			animPlayRepeat(&idleAnim);
		}

		else
			return;

	}

	if (InputSys::GetInstance()->inputs.onspacedown && !slashing) {

		animPlayOnce(&attackAnim);
		slashing = true;
		gruntSound->play();

	}

	if (slashing) {

		if (getCurrentFrame() == 3 && !backJump && !landing)
			attackSound->play();

		if(!backJump && getCurrentFrame() == 6)
			effect.stop();

		if (animLastFrameReached && !backJump) {

			animPlayOnce(&backJumpAnim);
			backJump = true;

		}

		if (backJump && getCurrentFrame() == 3 && !shortGruntSound->isPlaying() && !landing) {

			shortGruntSound->play();

		}

		if (animLastFrameReached && backJump) {

			if (!landing) {

				animPlayOnce(&landAnim);
				landing = true;

			}

			if (animLastFrameReached) {

				landing = false;
				backJump = false;
				slashing = false;
				animPlayRepeat(&idleAnim);

			}

		}

	}
	
	/*
	if (shrink) {

		scaleX = scaleX - Time::GetInstance()->deltaTime;
		scaleY = scaleX;

		imgResize();

		if (scaleX <= endScale)
			shrink = false;

	}

	else {

		scaleX = scaleX + Time::GetInstance()->deltaTime;
		scaleY = scaleX;

		imgResize();

		if (scaleX >= startScale)
			shrink = true;

	}
	*/
	/*
	glm::vec3 scale;

	scaleFactor += Time::GetInstance()->deltaTime * 90;

	if (scaleFactor >= 360)
		scaleFactor -= 360;
	//std::cout << std::cos(scaleFactor * M_PI / 180) << std::endl;
	scale.x = (std::cos(scaleFactor * M_PI / 180) * 0.25f + 0.75f) * startScale;
	scale.y = scale.x;

	setScale(scale);
	*/
}
