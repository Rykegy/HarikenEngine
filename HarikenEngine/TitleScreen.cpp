#include "stdafx.h"
#include "TitleScreen.h"
#include "TitlePicture.h"
#include "StartButton.h"
#include "QuitButton.h"
#include "HarikenText.h"
#include "DescText.h"
#include "LanguageMenu.h"

using namespace MEIUN;

void TitleScreen::onCreate()
{

	bgColor = glm::vec3(0.05f, 0.0f, 0.025f);

	titlepic = new TitlePicture();
	startbutt = new StartButton();
	quitbutt = new QuitButton();
	languageBar = new LanguageMenu();

	addObject(titlepic, "TitlePicture");
	addUI(startbutt, "StartButton");
	addUI(quitbutt, "StopButton");
	addUI(new HarikenText(), "TitleText");
	addUI(new DescText(), "TitleSubText");

	addUI(languageBar, "LanguageBar");

}

void TitleScreen::onStart() {

	startbutt->setPosition(-500.0f, -175.0f);
	startbutt->alignment.horizontal = HARIKEN::UIObject::Align::left;

	quitbutt->setPosition(-500.0f, -250.0f);
	quitbutt->alignment.horizontal = HARIKEN::UIObject::Align::left;

}
