#include "stdafx.h"
#include "LanguageMenu.h"

void MEIUN::LanguageMenu::onCreate()
{

	layer = 1;

	setImg(getAssetFile("TITLE")->getTexture("LanguageMenuBar.png"));

	setPosition(glm::vec2(150.0f, windowSize.y / 2 + 50.0f));

	alignment.horizontal = Align::left;
	alignment.vertical = Align::bottom;

	enButton = new LanguageSelectButton(u"English", EN);
	jpButton = new LanguageSelectButton(u"“ú–{Œê", JP);

	GameScene->addUI(enButton, "enButton");
	GameScene->addUI(jpButton, "jpButton");

	enButton->setPosition(-470.0f, 15.0f);
	jpButton->setPosition(-470.0f, -30.0f);

	lnShow = new languageShow();

	GameScene->addUI(lnShow, "lnShow");

	lnShow->setPosition(-470.0f, 15.0f);

}

void MEIUN::LanguageMenu::update()
{

	if (clicked == true && InputSys->inputs.Click.leftclickdown) {

		setImg(getAssetFile("TITLE")->getTexture("LanguageMenuBar.png"));
		clicked = false;
		lnShow->willRender = true;

		enButton->hide();
		jpButton->hide();

	}

	else if (onClick() && !clicked) {

		clicked = true;
		setImg(getAssetFile("TITLE")->getTexture("LanguageMenu.png"));
		lnShow->willRender = false;

		enButton->show();
		jpButton->show();

	}

}
