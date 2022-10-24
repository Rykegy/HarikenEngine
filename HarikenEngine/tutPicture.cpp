#include "stdafx.h"
#include "tutPicture.h"

void MEIUN::tutPicture::onCreate()
{

	layer = 1;

	setImg(getAssetFile("TUTASSET")->getTexture("Controls.png"));

	setScale(glm::vec3(0.25f));

	setPos(0.0f, 1.0f);

}

void MEIUN::tutPicture::update()
{
}
