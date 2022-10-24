/***************************************
UI Text button that is used to change languages.
***************************************/

#pragma once
#include "UIObject.h"
#include "stdafx.h"

namespace MEIUN {

	class LanguageSelectButton : public HARIKEN::UIObject
	{

	public:

		LanguageSelectButton(std::u16string buttonText_, Language language_);

		void show();
		void hide();

	private:

		void onCreate();

		void update();

		Language ln;
		std::u16string text;

		bool hidden = true;

	};

}