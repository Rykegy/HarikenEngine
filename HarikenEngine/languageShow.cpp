#include "stdafx.h"
#include "languageShow.h"

void MEIUN::languageShow::onCreate()
{

	setFont("YuGothB.ttc");
	setText(u"Language / ����", 22, glm::vec3(1.0f, 1.0f, 1.0f));
	alignment.horizontal = Align::left;
	layer = 0;

}

void MEIUN::languageShow::update()
{
}
