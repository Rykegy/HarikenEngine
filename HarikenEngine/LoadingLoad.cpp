#include "stdafx.h"
#include "LoadingLoad.h"

using namespace HARIKEN;

void HARIKEN::LoadingLoad::onCreate()
{

	en = getAssetFile("CORE")->getTexture("LoadEN.png");
	jp = getAssetFile("CORE")->getTexture("LoadJP.png");

	switch (ln = language) {

	case JP:
		setImg(jp);
		break;

	default:
		setImg(en);
		break;

	}

}

void HARIKEN::LoadingLoad::update()
{

	if (ln != language) {

		switch (ln = language) {

		case JP:
			setImg(jp);
			break;

		default:
			setImg(en);
			break;

		}

	}

}
