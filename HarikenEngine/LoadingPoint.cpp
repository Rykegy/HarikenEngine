#include "stdafx.h"
#include "LoadingPoint.h"

using namespace HARIKEN;

void HARIKEN::LoadingPoint::onCreate()
{

	setImg(getAssetFile("CORE")->getTexture("Point.png"));

}

void HARIKEN::LoadingPoint::update()
{
}
