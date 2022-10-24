/*************************************
UI in the title screen used to select languages.
*************************************/

#pragma once
#include "UIObject.h"
#include "LanguageSelectButton.h"
#include "languageShow.h"

namespace MEIUN {

	class LanguageMenu : public HARIKEN::UIObject
	{

	public:

		void onCreate();

		void update();

	private:

		bool clicked = false;

		LanguageSelectButton* enButton;
		LanguageSelectButton* jpButton;

		languageShow* lnShow;

	};

}