#pragma once
#include "Scene.h"
#include "BattleScene.h"

namespace MEIUN {

	class testBattleScene : public HARIKEN::Scene
	{
	public:
		testBattleScene();
		~testBattleScene();

		void onCreate();
		void onStart();

		virtual void update();

	};

}