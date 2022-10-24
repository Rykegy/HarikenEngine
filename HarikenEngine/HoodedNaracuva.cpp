#include "stdafx.h"
#include "HoodedNaracuva.h"
#include "roundSpherePartFount.h"

using namespace MEIUN;

float timer = 0.0f;

void MEIUN::HoodedNaracuva::onCreate()
{

	Name = "Hooded Naracuva";

	maxHP = 1000;
	maxMP = 1000;

	HP = 1000;
	MP = 1000;

	Level = 100;
	strength = 40;
	technique = 70;
	agility = 0;
	defence = 0;
	
	setUnitIcon(getAssetFile("TMPASSETS")->getTexture("HoodIco.jpg"));

	setIdleAnimation(getAssetFile("NARASSETS"), "Idle", "png", 0.2f);
	setAttackAnimation(getAssetFile("NARASSETS"), "Attack", "png", 0.1f);
	
	Hahaha = getAssetFile("NARASSETS")->getSound("NarLaugh0.wav");
	
	animPlayRepeat(getIdleAnimation());

	particleEffects.push_back(new HARIKEN::roundSpherePartFount());
	particleEffects[0]->stop();

}

void MEIUN::HoodedNaracuva::update()
{

	MEIUN::Unit::update();

}

void MEIUN::HoodedNaracuva::Attack()
{
	state = State::attack;

	if (getCurrentAnim() == getIdleAnimation()) {
		animPlayOnce(getAttackAnimation());
		if (!Hahaha->isPlaying())
			Hahaha->play();
	}

	if (animLastFrameReached || getCurrentAnim() == nullptr) {

		setPos(3.0f, 0.0f);
		showOpponent();
		inflictDamage();
		animPlayOnce(nullptr);
		particleEffects[0]->play();

		if (timer > 0.5f)
			particleEffects[0]->stop();

		if (timer > 2.5f) {
			//particleEffects[0]->stop();
			setPos(0.0f, 0.0f);
			state = State::idle;
			willRender = false;
			timer = 0.0f;
			turnEnd();
		}

		else {
			timer += time->deltaTime;
			
		}

	}

}
