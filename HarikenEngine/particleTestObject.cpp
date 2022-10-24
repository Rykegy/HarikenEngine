#include "stdafx.h"
#include "particleTestObject.h"

using namespace HARIKEN;

void HARIKEN::particleTestObject::onCreate()
{

	pos = glm::vec3(8, 4.5, 0);

	particleEffects.push_back(new roundSpherePartFount());

}

void HARIKEN::particleTestObject::update()
{
}
