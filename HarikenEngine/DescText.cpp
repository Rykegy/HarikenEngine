#include "stdafx.h"
#include "DescText.h"

using namespace MEIUN;

void DescText::onCreate()
{

	setFont("BIZ-UDGothicR.ttc");
	switch(lang = language) {

	case JP:
		setText(u"エンジンデモンストレーション -バージョンα3.1-", 24, glm::vec3(1.0f, 0.25f, 0.0f));
		break;

	default:
		setText(u"Engine demo -Ver. Alpha 3.1-", 24, glm::vec3(1.0f, 0.25f, 0.0f));

	}
	setPosition(-500.0f, 140.0f);
	alignment.vertical = Align::center;
	alignment.horizontal = Align::left;

}

void DescText::update()
{

	if (lang != language) {
		switch (lang = language) {

		case JP:
			setText(u"エンジンデモンストレーション-バージョンα3.0-", 24, glm::vec3(1.0f, 0.25f, 0.0f));
			break;

		default:
			setText(u"Engine demo -Ver. Alpha 3.0-", 24, glm::vec3(1.0f, 0.25f, 0.0f));

		}
	}

}
