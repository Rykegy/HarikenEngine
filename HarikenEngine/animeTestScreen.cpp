#include "stdafx.h"
#include "animeTestScreen.h"
#include "AnimationTestObj.h"

using namespace HARIKEN;

animeTestScreen::animeTestScreen()
{

	bgColor = glm::vec3(1.0f, 1.0f, 1.0f);

}


animeTestScreen::~animeTestScreen()
{

}

void HARIKEN::animeTestScreen::onCreate()
{

	Anime = new AnimationTestObj();
	addObject(Anime, "Anime");

}

void HARIKEN::animeTestScreen::onStart()
{
}
