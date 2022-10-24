#include "stdafx.h"
#include "Black.h"
#include "BattleScene.h"

using namespace MEIUN;

void MEIUN::Black::onCreate()
{

	Name = "Cynthia";

	maxHP = 100;
	maxMP = 100;

	HP = 100;
	MP = 100;

	Level = 1;
	strength = 10;
	technique = 10;
	agility = 10;
	defence = 10;

	setUnitIcon(getAssetFile("BLKETC")->getTexture("BlackIco.jpg"));

	ShortGrunt = getAssetFile("BLKETC")->getSound("BlkShortGrunt3.wav");
	Grunt = getAssetFile("BLKETC")->getSound("BlkGrunt0.wav");
	LongGrunt = getAssetFile("BLKETC")->getSound("BlkLongGrunt2.wav");
	SharpGrunt = getAssetFile("BLKETC")->getSound("BlkSharpGrunt.wav");
	Charge = getAssetFile("BLKETC")->getSound("BlkCharge.wav");
	
	afterImageEffect = new HARIKEN::AfterImageEffect();
	afterImageEffect->layer = layer + 1;
	
	powerUp = new HARIKEN::Animation2DSequence(createAnimation(getAssetFile("BLKANIM"), "BattleScenePowerUp", "png", 0.1f));

	Skill* rage = new Skill("Rage", 25, 0, 0, 50.0f, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, powerUp, afterImageEffect, Charge, 3, "[MP Cost: 25] Increases the strength of the next attack by 50% and makes it a critical hit.", "HAAA!!!");
	rage->addLanguageOption(JP, u"怒り", u"[MPコスト:25]次の攻撃の威力は50%上りすると、必ずクリティカルヒットになります。", u"ハアッ！！！");
	addSkill(rage);

	Skill* mindEye = new Skill("Mind's Eye", 25, 0, 0, 0.0f, 0.0f, 50.0f, 0.0f, 50.0f, 50.0f, powerUp, nullptr, ShortGrunt, 0, "[MP Cost: 25] Increases Consistancy/Accuracy/Agility by 50% for 1 turn", "...");
	mindEye->addLanguageOption(JP, u"心眼", u"[MPコスト: 25]命中/固定力/移動力全５０％上がります。", u".....");
	addSkill(mindEye);

	slashWaveEffect = new HARIKEN::SlashWave();
	addParticleEffect(slashWaveEffect);

	brilliantEndAnim = new HARIKEN::Animation2DSequence(createAnimation(getAssetFile("BLKANIM"), "BattleBrilliantEnd", "png", 0.1f));
	Tech* brilliantEnd = new Tech("Brilliant End", 0, 0, 0, 999999999.0f, 0.0f, 100.0f, 100.0f, 100.0f, 0.0f, brilliantEndAnim, -1, "Sacrifice all HP to unleash a devastating attack", "Let's end this!");
	brilliantEnd->addLanguageOption(JP, u"ブリリアントエンド", u"全体力使ってえいるの超強力な攻撃。", u"全力に決めるぞ！");
	addTech(brilliantEnd);

	setIdleAnimation(getAssetFile("BLKANIM"), "BattleSceneIdle", "png", 0.1f);
	setAttackAnimation(getAssetFile("BLKANIM"), "BattleSceneAttack", "png", 0.05f);

	animPlayRepeat(getIdleAnimation());
	setPos(0, 0);
	setScale(glm::vec3(1.0, 1.0, 1));

}

void MEIUN::Black::update()
{

	MEIUN::Unit::update();

	afterImageEffect->setPos(getCurrentAnim()->getFrame(getCurrentFrame())->getPosition());
	afterImageEffect->getParticleProperties()->particleTexture = getCurrentAnim()->getTextureForFrame(getCurrentFrame());
	float maxImageSize = std::fmax(afterImageEffect->getParticleProperties()->particleTexture->size.x, afterImageEffect->getParticleProperties()->particleTexture->size.y);
	afterImageEffect->getParticleProperties()->scale = getScale() * maxImageSize;

	if (state == State::tech && getCurrentTech()->name == u"Brilliant End") {

		if(getCurrentAnim() != brilliantEndAnim)
			animPlayOnce(brilliantEndAnim);

		if (getCurrentFrame() == 2 && techTimer < 1.0f) {

			animPause();
			techTimer += time->deltaTime;

		}

		else if (getCurrentFrame() == 2 && techTimer >= 1.0f) {

			animPlay();

		}

		if (getCurrentFrame() == 3 && techTimer != 0.0f)
			techTimer = 0.0f;

		if (getCurrentFrame() == 6) {

			switch (language) {

			case JP:
				battleText = u"ハアアアアアアア！！！";
				break;

			default:
				battleText = u"HAAAAAA!!!";
				break;

			}

			if(!SharpGrunt->isPlaying())
				SharpGrunt->play();

		}

		if (getCurrentFrame() == 8)
			slashWaveEffect->play();

		if (animLastFrameReached) {

			velocity.x = 5.0f;
			techTimer += time->deltaTime;

			if (techTimer == 0.0f) {

				//LongCry->play();

			}

			if (techTimer >= 2.0f && techTimer <= 5.0f) {

				slashWaveEffect->stop();

			}

			if (techTimer > 5.0f) {

				velocity.x = 0.0f;
				setPos(10.0f, 0.0f);
				slashWaveEffect->play();
				showOpponent();

			}

			if (techTimer > 7.0f) {

				inflictDamage();
				getBattleScene()->HealthCut(this, maxHP);
				if (HP < 0)
					HP = 0;
				slashWaveEffect->stop();

			}

			if (techTimer > 10.0f) {

				turnEnd();
				techTimer = 0.0f;
				setPos(0.0f, 0.0f);

			}

		}

	}

}

void MEIUN::Black::Attack()
{

	if (getCurrentAnim() != getAttackAnimation()) {

		state = State::attack;

		animPlayOnce(getAttackAnimation());

	}

	if (getCurrentFrame() <= 13) {

		switch (language) {

		case JP:
			battleText = u"行くぞ！";
			break;

		default:
			battleText = u"Let's Go!";
			break;

		}

	}

	else
		battleText = u"";

	if (getCurrentFrame() == 7) {

		if (!Grunt->isPlaying())
			Grunt->play();

	}

	//if (getCurrentFrame() == 19 && !MidCry->isPlaying())
		//MidCry->play();

	if (getCurrentFrame() > 19 && getCurrentFrame() <= 29) {

		switch (language) {

		case JP:
			battleText = u"ハアアアアア！";
			break;

		default:
			battleText = u"HAAAAAH!";
			break;

		}

	}

	if (getCurrentFrame() == 16)
		showOpponent();

	if (getCurrentFrame() == 22)
		if (!LongGrunt->isPlaying())
			LongGrunt->play();

	if (getCurrentFrame() == 24)
		inflictDamage();

	if (animLastFrameReached) {

		if (timer > 1.0f) {
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
