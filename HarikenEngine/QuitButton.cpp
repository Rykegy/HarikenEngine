#include "stdafx.h"
#include "QuitButton.h"
#include "sceneManager.h"

using namespace MEIUN;

void QuitButton::onCreate()
{
	
	setFont("YuGothB.ttc");

	switch (lang = language) {

	case JP:
		setText(u"I—¹", 36, glm::vec3(1.0f, 1.0f, 1.0f));
		break;

	default:
		setText(u"Quit", 36, glm::vec3(1.0f, 1.0f, 1.0f));
		break;

	}

	alignment.horizontal = Align::left;
	alignment.vertical = Align::center;

}

void QuitButton::update()
{

	if (lang != language) {

		switch (lang = language) {

		case JP:
			setText(u"I—¹", 36, glm::vec3(1.0f, 1.0f, 1.0f));
			break;

		default:
			setText(u"Quit", 36, glm::vec3(1.0f, 1.0f, 1.0f));
			break;

		}

	}

	if(onClick())
		sceneManager->loadLevel("Exit");

}