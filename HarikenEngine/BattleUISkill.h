/********************************************************************************************************************************
UI Text button that holds the name of a particular skill. When hovered over, displays the functionality of that skill and when clicked, uses the skill represented.
********************************************************************************************************************************/

#pragma once
#include "UIObject.h"
#include "Unit.h"

namespace MEIUN {

	class BattleScene;

	class BattleUISkill : public HARIKEN::UIObject
	{
	public:

		BattleUISkill(const Skill* skill_, int skillNumber);
		
		void onCreate();
		void update();

	private:

		const Skill* skill;
		int skillNumber;

		UIObject* descriptionText;
		UIObject* descriptionBox;

		bool mouseOvered = false;

		BattleScene* battleScene;

		std::u16string name;
		std::u16string description;

	};

}