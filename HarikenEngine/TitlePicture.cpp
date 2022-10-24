#include "stdafx.h"
#include "TitlePicture.h"
#include <math.h>
#include<iostream>
#include "WindowSys.h"

using namespace MEIUN;

void TitlePicture::onCreate() {

	setImg(getAssetFile("TITLE")->getTexture("BlackNoBG.png"));

	glm::vec3 scale;

	glm::vec2 windowSize = Window->getWinSize();

	if (image->size.y > windowSize.y || image->size.x > windowSize.y) {

		if (image->size.y - windowSize.y > image->size.x - windowSize.x) {

			scale.x = windowSize.y / image->size.y;
			scale.y =  scale.x;

		}

		else {

			scale.x = windowSize.x / image->size.x;
			scale.y = scale.x;

		}

	}

	setScale(scale);

	setPos(4.0f, 0.0f);

}

void TitlePicture::update() {



}