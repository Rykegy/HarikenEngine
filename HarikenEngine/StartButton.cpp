#include "stdafx.h"
#include "StartButton.h"

using namespace MEIUN;

void StartButton::onCreate()
{

	setFont("YuGothB.ttc");

	switch (lang = language) {

	case JP:
		setText(u"スタート", 56, glm::vec3(1.0f, 1.0f, 1.0f));
		break;

	default:
		setText(u"Start", 56, glm::vec3(1.0f, 1.0f, 1.0f));
		break;

	}

	alignment.horizontal = Align::left;
	alignment.vertical = Align::center;

}

void StartButton::update()
{

	if (lang != language) {

		switch (lang = language) {

		case JP:
			setText(u"スタート", 72, glm::vec3(1.0f, 1.0f, 1.0f));
			break;

		default:
			setText(u"Start", 72, glm::vec3(1.0f, 1.0f, 1.0f));
			break;

		}

	}

	if(onClick())
		sceneManager->loadLevel("next");

}