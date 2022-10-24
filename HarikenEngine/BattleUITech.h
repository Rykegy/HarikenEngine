/***********************************************************************************************************************************************
UI Text button that holds the name of a particular technique. When hovered over, displays the functionality of that technique and when clicked, uses the technique represented.
***********************************************************************************************************************************************/

#pragma once
#include "Unit.h"
#include "UIObject.h"

namespace MEIUN {

	class BattleScene;

	class BattleUITech : public HARIKEN::UIObject
	{
	public:

		BattleUITech(const Tech* tech_, int techNumber_);

		void onCreate();
		void update();

	private:

		const Tech* tech;
		int techNumber;

		UIObject* descriptionText;
		UIObject* descriptionBox;

		bool mouseOvered = false;

		BattleScene* battleScene;

		std::u16string name;
		std::u16string description;

	};

}