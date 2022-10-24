#include "stdafx.h"
#include "Unit.h"
#include "BattleScene.h"

using namespace MEIUN;

Unit::Unit()
{

	Window = HARIKEN::WindowSys::GetInstance();
	sceneManager = HARIKEN::SceneManager::GetInstance();

}

void MEIUN::Unit::update()
{

	switch (state) {

	case State::attack:
		Attack();
		skillSoundPlayed = false;
		break;

	case State::idle:
		if (getCurrentAnim() != getIdleAnimation()) {
			battleText = u"";
			animPlayRepeat(getIdleAnimation());
		}
		skillSoundPlayed = false;
		break;

	case State::skill:
		if (getCurrentAnim() != currentSkill->animation) {
			if (currentSkill->getLanguageOption() != nullptr)
				battleText = currentSkill->getLanguageOption()->dialogue;
			else
				battleText = currentSkill->dialogue;
			animPlayOnce(currentSkill->animation);
		}
		else {
			if (animLastFrameReached) 
				state = State::idle;
		}
		if(getCurrentFrame() == currentSkill->effectStartFrame)
			if (currentSkill->effect != nullptr)
				currentSkill->effect->play();
		if(currentSkill->sound != nullptr)
			if (!skillSoundPlayed) {
				currentSkill->sound->play();
				skillSoundPlayed = true;
			}
		break;

	default:
		break;

	}

}

void MEIUN::Unit::unitInit()
{
	turnAttackValue = strength;
	turnDefenceValue = defence;
	turnAgilityValue = agility;
	turnAccuracyModifier = technique - Level * 10;
	turnCritModifier = agility / 2 + technique / 2 - Level;
	turnConsistancyModifier = agility / 2 + technique / 2 - Level * 10;
	battleScene = static_cast<BattleScene*>(GameScene);
}

std::vector<Tech*>* MEIUN::Unit::getTechList()
{
	return &techList;
}

std::vector<Skill*>* MEIUN::Unit::getSkillList()
{
	return &skillList;
}

const HARIKEN::Texture * MEIUN::Unit::getUnitIcon()
{
	return unitIcon;
}

void MEIUN::Unit::Attack()
{

	state = State::attack;
	inflictDamage();
	state = State::idle;
	turnEnd();

}

void MEIUN::Unit::startDodge()
{

	state = State::dodge;
	layer = 0;
	state = State::idle;

}

void MEIUN::Unit::endDodge()
{

	state = State::idle;

}

void MEIUN::Unit::useSkill(const Skill * useSkill)
{

	Skill* skill = nullptr;

	for (auto s : skillList)
		if (s == useSkill) {
			skill = s;
		}

	if (skill == nullptr)
		return;

	if (MP - skill->cost < 0 || skill->used == true)
		return;

	for (auto s : skillList)
		if (s == skill) {
			currentSkill = s;
			break;
		}

	turnAttackModifier += std::round(currentSkill->strengthMod / 100.0f);
	turnDefenceModifier += std::round(currentSkill->defenceMod / 100.0f);
	turnAgilityModifier += std::round(currentSkill->agilityMod / 100.0f);
	turnAccuracyModifier += currentSkill->accuracyMod;
	turnConsistancyModifier += currentSkill->consistancyMod;
	turnCritModifier += currentSkill->criticalChanceGain;

	state = State::skill;

	battleScene->manaCut(this, skill->cost);

	skill->used = true;

}

void MEIUN::Unit::useTech(const Tech * tech)
{

	if (MP - tech->cost < 0)
		return;

	for(auto t : techList)
		if (t == tech) {
			currentTech = t;
			break;
		}

	state = State::tech;

	turnAttackModifier += std::round(currentTech->strengthMod / 100.0f);
	turnDefenceModifier += std::round(currentTech->defenceMod / 100.0f);
	turnAgilityModifier += std::round(currentTech->agilityMod / 100.0f);
	turnAccuracyModifier += currentTech->accuracyMod;
	turnConsistancyModifier += currentTech->consistancyMod;
	turnCritModifier += currentTech->criticalChanceGain;

	battleScene->manaCut(this, tech->cost);

}

State MEIUN::Unit::getState()
{

	return state;

}

const Tech * MEIUN::Unit::getCurrentTech()
{
	return currentTech;
}

std::u16string MEIUN::Unit::getBattleText()
{
	return battleText;
}

void MEIUN::Unit::turnStart()
{

	turnAttackValue = strength;
	turnDefenceValue = defence;
	turnAgilityValue = agility;
	turnAttackModifier = 0.0f;
	turnDefenceModifier = 0.0f;
	turnAgilityModifier = 0.0f;
	turnAccuracyModifier = technique - Level;
	turnCritModifier = agility / 2 + technique / 2 - Level;
	turnConsistancyModifier = agility / 2 + technique / 2 - Level;

	if (MP < maxMP) {

		int temp = maxMP / 10;

		if (MP + temp > maxMP)
			temp = maxMP - MP;

		battleScene->manaCut(this, -temp);

	}

	for (auto s : skillList)
		s->used = false;

	willRender = true;

	layer = 1;

}

void MEIUN::Unit::setUnitIcon(const HARIKEN::Texture* texture)
{

	unitIcon = texture->copy();

	if ((std::max)(unitIcon->size.x, unitIcon->size.y) != 150.0f * *Window->windowScale) {

		unitIcon->size *= (150.0f * *Window->windowScale) / (std::max)(unitIcon->size.x, unitIcon->size.y);

	}

}

void MEIUN::Unit::addSkill(Skill* newSkill)
{

	skillList.push_back(newSkill);

	if (newSkill->effect == nullptr)
		return;

	addParticleEffect(newSkill->effect);
	newSkill->effect->stop();

}

void MEIUN::Unit::addTech(Tech* newTech)
{

	techList.push_back(newTech);
	//addParticleEffect(newTech->effect);
	//newTech->effect->stop();

}

void MEIUN::Unit::turnEnd()
{

	for (auto p : particleEffects)
		p->stop();

	willRender = false;

	layer = 2;

	battleScene->switchTurn();

}

void MEIUN::Unit::setIdleAnimation(HARIKEN::AssetFile* assetFile, std::string animationName, std::string ext, float speed)
{

	idle = HARIKEN::Animation2D::createAnimation(assetFile, animationName, ext, speed);

}

void MEIUN::Unit::setHurtAnimation(HARIKEN::AssetFile* assetFile, std::string animationName, std::string ext, float speed)
{
	
	hurt = HARIKEN::Animation2D::createAnimation(assetFile, animationName, ext, speed);

}

void MEIUN::Unit::setAttackAnimation(HARIKEN::AssetFile* assetFile, std::string animationName, std::string ext, float speed)
{
	
	attack = HARIKEN::Animation2D::createAnimation(assetFile, animationName, ext, speed);

}

void MEIUN::Unit::setGuardAnimation(HARIKEN::AssetFile* assetFile, std::string animationName, std::string ext, float speed)
{
	
	guard = HARIKEN::Animation2D::createAnimation(assetFile, animationName, ext, speed);

}

void MEIUN::Unit::setDodgeAnimation(HARIKEN::AssetFile* assetFile, std::string animationName, std::string ext, float speed)
{
	
	dodge = HARIKEN::Animation2D::createAnimation(assetFile, animationName, ext, speed);

}

void MEIUN::Unit::manaCut(int amount)
{

	battleScene->manaCut(this, amount);

}

void MEIUN::Unit::healthCut(int amount)
{

	battleScene->HealthCut(this, amount);

}



HARIKEN::Animation2DSequence * MEIUN::Unit::getIdleAnimation()
{
	return &idle;
}

HARIKEN::Animation2DSequence * MEIUN::Unit::getHurtAnimation()
{
	return &hurt;
}

HARIKEN::Animation2DSequence * MEIUN::Unit::getAttackAnimation()
{
	return &attack;
}

HARIKEN::Animation2DSequence * MEIUN::Unit::getGuardAnimation()
{
	return &guard;
}

HARIKEN::Animation2DSequence * MEIUN::Unit::getDodgeAnimation()
{
	return &dodge;
}

void MEIUN::Unit::inflictDamage()
{

	turnAttackValue *= (turnAttackModifier + 1.0f);
	turnDefenceValue *= (turnDefenceModifier + 1.0f);
	turnAgilityValue *= (turnAgilityModifier + 1.0f);

	battleScene->inflictDamage();

}

void MEIUN::Unit::showOpponent()
{

	battleScene->showOpponent();
	
}

BattleScene * MEIUN::Unit::getBattleScene()
{
	return battleScene;
}

bool MEIUN::Unit::willCrit()
{

	float chanceNumber = 20.0f * Level;

	if (agility == 0)
		return false;

	if (static_cast <int> (rand()) / (static_cast <float> (RAND_MAX / (technique))) + static_cast <int> (rand()) / (static_cast <float> (RAND_MAX / (agility))) > chanceNumber - chanceNumber * turnCritModifier / 100.0f)
		return true;

	return false;
}

void MEIUN::Skill::addLanguageOption(Language language_, std::string name_, std::string description_, std::string dialogue_)
{

	languageOptions[language_] = languageOption(conversions::to_u16string(name_), conversions::to_u16string(description_), conversions::to_u16string(dialogue_));

}

void MEIUN::Skill::addLanguageOption(Language language_, std::u16string name_, std::u16string description_, std::u16string dialogue_)
{

	languageOptions[language_] = languageOption(name_, description_, dialogue_);

}

const MEIUN::Skill::languageOption* MEIUN::Skill::getLanguageOption() const
{

	if (languageOptions.find(language) != languageOptions.end())
		return &languageOptions.at(language);

	return nullptr;

}

void MEIUN::Tech::addLanguageOption(Language language_, std::string name_, std::string description_, std::string dialogue_)
{

	languageOptions[language_] = languageOption(conversions::to_u16string(name_), conversions::to_u16string(description_), conversions::to_u16string(dialogue_));

}

void MEIUN::Tech::addLanguageOption(Language language_, std::u16string name_, std::u16string description_, std::u16string dialogue_)
{

	languageOptions[language_] = languageOption(name_, description_, dialogue_);

}

const MEIUN::Tech::languageOption* MEIUN::Tech::getLanguageOption() const
{

	if (languageOptions.find(language) != languageOptions.end())
		return &languageOptions.at(language);

	return nullptr;

}
