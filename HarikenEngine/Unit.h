/****************************************************
Class to be inherited to contain unit data that is used for battles.
****************************************************/

#pragma once
#include "GameObject.h"
#include "Animation2D.h"
#include "AssetHandler.h"
#include "GLOBAL_VALUES.h"
#include "NiftyConversions.h"

namespace MEIUN {

	struct Tech {

		std::u16string name;
		int cost;
		
		int HPGain = 0;
		int MPGain = 0;
		float strengthMod = 0.0f;
		float defenceMod = 0.0f;
		float consistancyMod = 0.0f;
		float criticalChanceGain = 0;
		float accuracyMod = 0.0f;
		float agilityMod = 0.0f;

		HARIKEN::Animation2DSequence* animation;
		int damageInflictFrame = 0;

		std::u16string description;
		std::u16string dialogue;

		Tech(std::string name_, int cost_, int HPGain_, int MPGain_, float strengthMod_, float defenceMod_, float consistancyMod_, float criticalChanceGain_, float accuracyMod_, float agilityMod_, HARIKEN::Animation2DSequence* animation_, int effectStartFrame_, std::string description_, std::string dialogue_) {

			name = conversions::to_u16string(name_);
			cost = cost_;
			HPGain = HPGain_;
			MPGain = MPGain_;
			strengthMod = strengthMod_;
			defenceMod = defenceMod_;
			consistancyMod = consistancyMod_;
			criticalChanceGain = criticalChanceGain_;
			accuracyMod = accuracyMod_;
			agilityMod = agilityMod_;
			animation = animation_;
			description = conversions::to_u16string(description_);
			dialogue = conversions::to_u16string(dialogue_);

		}

		Tech(std::u16string name_, int cost_, int HPGain_, int MPGain_, float strengthMod_, float defenceMod_, float consistancyMod_, float criticalChanceGain_, float accuracyMod_, float agilityMod_, HARIKEN::Animation2DSequence* animation_, int effectStartFrame_, std::u16string description_, std::u16string dialogue_) {

			name = name_;
			cost = cost_;
			HPGain = HPGain_;
			MPGain = MPGain_;
			strengthMod = strengthMod_;
			defenceMod = defenceMod_;
			consistancyMod = consistancyMod_;
			criticalChanceGain = criticalChanceGain_;
			accuracyMod = accuracyMod_;
			agilityMod = agilityMod_;
			animation = animation_;
			description = description_;

		}

		struct languageOption {

			std::u16string name;
			std::u16string description;
			std::u16string dialogue;

			languageOption() {

				name = u"";
				description = u"";
				dialogue = u"";

			}

			languageOption(std::u16string name_, std::u16string description_, std::u16string dialogue_) {

				name = name_;
				description = description_;
				dialogue = dialogue_;

			}

		};

		std::map<Language, languageOption> languageOptions;

	public:

		void addLanguageOption(Language language_, std::string name_, std::string description_, std::string dialogue_);
		void addLanguageOption(Language language_, std::u16string name_, std::u16string description_, std::u16string dialogue_);
		const languageOption* getLanguageOption() const;

	};

	struct Skill {

		std::u16string name;
		int cost;

		int HPGain = 0;
		int MPGain = 0;
		float strengthMod = 0.0f;
		float defenceMod = 0.0f;
		float consistancyMod = 0.0f;
		float criticalChanceGain = 0;
		float accuracyMod = 0.0f;
		float agilityMod = 0.0f;

		bool used = false;

		std::u16string description = u"";
		std::u16string dialogue = u"";

		HARIKEN::Animation2DSequence* animation; 
		HARIKEN::Sound* sound;

		HARIKEN::ParticleEffects* effect;
		int effectStartFrame = 0;

		Skill(std::string name_, int cost_, int HPGain_, int MPGain_, float strengthMod_, float defenceMod_, float consistancyMod_, float criticalChanceGain_, float accuracyMod_, float agilityMod_, HARIKEN::Animation2DSequence* animation_, HARIKEN::ParticleEffects* effect_, HARIKEN::Sound* sound_, int effectStartFrame_, std::string description_, std::string dialogue_) {

			name = conversions::to_u16string(name_);
			cost = cost_;
			HPGain = HPGain_;
			MPGain = MPGain_;
			strengthMod = strengthMod_;
			defenceMod = defenceMod_;
			consistancyMod = consistancyMod_;
			criticalChanceGain = criticalChanceGain_;
			accuracyMod = accuracyMod_;
			agilityMod = agilityMod_;
			animation = animation_;
			description = conversions::to_u16string(description_);
			dialogue = conversions::to_u16string(dialogue_);
			effect = effect_;
			sound = sound_;
			effectStartFrame = effectStartFrame_;

		}

		Skill(std::u16string name_, int cost_, int HPGain_, int MPGain_, float strengthMod_, float defenceMod_, float consistancyMod_, float criticalChanceGain_, float accuracyMod_, float agilityMod_, HARIKEN::Animation2DSequence* animation_, HARIKEN::ParticleEffects* effect_, HARIKEN::Sound* sound_, int effectStartFrame_, std::u16string description_, std::u16string dialogue_) {

			name = name_;
			cost = cost_;
			HPGain = HPGain_;
			MPGain = MPGain_;
			strengthMod = strengthMod_;
			defenceMod = defenceMod_;
			consistancyMod = consistancyMod_;
			criticalChanceGain = criticalChanceGain_;
			accuracyMod = accuracyMod_;
			agilityMod = agilityMod_;
			animation = animation_;
			description = description_;
			dialogue = dialogue_;
			effect = effect_;
			sound = sound_;
			effectStartFrame = effectStartFrame_;

		}

	private:

		struct languageOption {

			std::u16string name;
			std::u16string description;
			std::u16string dialogue;

			languageOption() {

				name = u"";
				description = u"";
				dialogue = u"";

			}

			languageOption(std::u16string name_, std::u16string description_, std::u16string dialogue_) {

				name = name_;
				description = description_;
				dialogue = dialogue_;

			}

		};

		std::map<Language, languageOption> languageOptions;

	public:

		void addLanguageOption(Language language_, std::string name_, std::string description_, std::string dialogue_);
		void addLanguageOption(Language language_, std::u16string name_, std::u16string description_, std::u16string dialogue_);
		const languageOption* getLanguageOption() const;

	};

	enum State
	{

		idle,
		attack,
		skill,
		tech,
		dodge

	};

	class BattleScene;

	class Unit : public HARIKEN::GameObject
	{

	public:
		Unit();

		virtual void onCreate() = 0;
		virtual void update();

		virtual Unit* clone() const = 0;

		void unitInit();

		std::string Name = "Unit";

		int Level;
		int maxHP;
		int maxMP;
		int HP;
		int MP;
		int strength;
		int technique;
		int agility;
		int defence;

		std::vector<Tech*>* getTechList();
		std::vector<Skill*>* getSkillList();

		const HARIKEN::Texture* getUnitIcon();

		virtual void Attack();
		virtual void startDodge();
		void endDodge();
		void useSkill(const Skill* skill);
		void useTech(const Tech* tech);

		State getState();

		const Tech* getCurrentTech();

		std::u16string getBattleText();

		int turnAttackValue;
		int turnDefenceValue;
		int turnAgilityValue;
		float turnAttackModifier;
		float turnDefenceModifier;
		float turnAgilityModifier;
		float turnAccuracyModifier;
		float turnCritModifier;
		float turnConsistancyModifier;

		void turnStart();
		bool willCrit();

	protected:

		void setUnitIcon(const HARIKEN::Texture* texture);

		void addSkill(Skill*);
		void addTech(Tech*);
		void turnEnd();

		void setIdleAnimation(HARIKEN::AssetFile* assetFile, std::string animationName, std::string ext, float speed);
		void setHurtAnimation(HARIKEN::AssetFile* assetFile, std::string animationName, std::string ext, float speed);
		void setAttackAnimation(HARIKEN::AssetFile* assetFile, std::string animationName, std::string ext, float speed);
		void setGuardAnimation(HARIKEN::AssetFile* assetFile, std::string animationName, std::string ext, float speed);
		void setDodgeAnimation(HARIKEN::AssetFile* assetFile, std::string animationName, std::string ext, float speed);

		void manaCut(int amount);
		void healthCut(int amount);

		HARIKEN::Animation2DSequence* getIdleAnimation();
		HARIKEN::Animation2DSequence* getHurtAnimation();
		HARIKEN::Animation2DSequence* getAttackAnimation();
		HARIKEN::Animation2DSequence* getGuardAnimation();
		HARIKEN::Animation2DSequence* getDodgeAnimation();

		State state = State::idle;

		std::u16string battleText;

		void inflictDamage();
		void showOpponent();

		BattleScene* getBattleScene();

	private:

		std::vector<Tech*>techList;
		std::vector<Skill*>skillList;

		HARIKEN::Texture* unitIcon; //Icon is 150 x 150

		HARIKEN::Animation2DSequence idle;
		HARIKEN::Animation2DSequence hurt;
		HARIKEN::Animation2DSequence attack;
		HARIKEN::Animation2DSequence guard;
		HARIKEN::Animation2DSequence dodge;

		const Skill* currentSkill;
		const Tech* currentTech;

		BattleScene* battleScene;

		bool skillSoundPlayed = false;

	};

	template <typename Derived>
	class derivedUnit : public Unit {

		virtual Unit* clone() const {

			return new Derived(static_cast<Derived const&> (*this));

		}

	};

}