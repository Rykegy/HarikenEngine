#include "stdafx.h"
#include "ParticleTest.h"
#include "particleTestObject.h"

using namespace HARIKEN;

ParticleTest::ParticleTest()
{

	bgColor = glm::vec3(0.0f, 0.0f, 0.0f);

}


ParticleTest::~ParticleTest()
{
}

void HARIKEN::ParticleTest::onCreate()
{

	addObject(new particleTestObject, "Test");

}

void HARIKEN::ParticleTest::onStart()
{

}
