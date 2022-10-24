#include "stdafx.h"
#include "TextTest.h"

using namespace MEIUN;

void HarikenText::onCreate()
{

	setFont("UDDigiKyokashoN-B.ttc");
	setText(u"HARIKEN", 72, glm::vec3(1.0f, 0.25f, 0.0f));
	setPosition(-500.0f, 200.0f);

	alignment.horizontal = Align::left;
	alignment.vertical = Align::center;

}

void HarikenText::update()
{


}
