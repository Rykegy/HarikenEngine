/***********************************************************************************
List of scenes to be used in the game. The starting scene MUST be put at the top of the list. 
***********************************************************************************/

#pragma once
#include <vector>

#include "TitleScreen.h"
#include "levelone.h"
#include "leveltwo.h"
#include "EndScene.h"
#include "OpenGLTest.h"
#include "ScottTest.h"
#include "animeTestScreen.h"
#include "CollisionTest.h"
#include "ParticleTest.h"
#include "testBattleScene.h"
#include "testEncounterMap.h"
#include "BattleScene.h"

const std::vector<HARIKEN::Scene*> SCENE_LIST = {

	//Add Scenes here

	//new HARIKEN::OpenGLTest()
	//new HARIKEN::ScottTest(),
	//new MEIUN::TitleScreen(),
	//new HARIKEN::animeTestScreen()
	//new HARIKEN::ParticleTest()
	//new HARIKEN::CollisionTest()
	new MEIUN::testEncounterMap()
	//static_cast<HARIKEN::Scene*>(new MEIUN::BattleScene(nullptr, nullptr, nullptr))
	//new HARIKEN::levelone()
	//new HARIKEN::leveltwo()
	//HARIKEN::new EndScene()
	//new MEIUN::testBattleScene()

};