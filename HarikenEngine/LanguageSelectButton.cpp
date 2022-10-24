#include "stdafx.h"
#include "LanguageSelectButton.h"

MEIUN::LanguageSelectButton::LanguageSelectButton(std::u16string buttonText_, Language language_)
{

	text = buttonText_;
	ln = language_;

}

void MEIUN::LanguageSelectButton::show()
{
	hidden = false;
	
}

void MEIUN::LanguageSelectButton::hide()
{

	hidden = true;

}

void MEIUN::LanguageSelectButton::onCreate()
{

	setFont("YuGothB.ttc");
	setText(text, 22, glm::vec3(1.0f, 1.0f, 1.0f));
	alignment.horizontal = Align::left;

	layer = 0;

}

void MEIUN::LanguageSelectButton::update()
{

	if (willRender && onClick()) {

		language = ln;

		FILE* fptr;

		fopen_s(&fptr, "config", "wb");
		fwrite(&language, sizeof(Language), 1, fptr);

		fclose(fptr);

	}

	if (hidden)
		willRender = false;

	else
		willRender = true;

}
