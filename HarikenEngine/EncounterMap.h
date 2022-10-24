/***************************************************************
Overworld map to be inherited and designed as seperate levels for the game.
***************************************************************/

#pragma once
#include "MapPlayer.h"
#include "Unit.h"
#include "BattleScene.h"
#include <random>

namespace MEIUN {

	class EncounterMap : public HARIKEN::Scene
	{
	public:

		EncounterMap();
		~EncounterMap();

		virtual void onCreate() = 0;
		virtual void onStart() = 0;
		virtual HARIKEN::Scene* clone() = 0;

		Unit* getEnemy(int enemyIndex);
		Unit* getRandomEnemy();

		battleResult startBattle();
		battleResult startBattle(Unit* enemy);

	protected:

		void addEnemy(Unit*);
		void setBattleBGM(HARIKEN::Sound* BGM);

		MapPlayer* Player;

	private:

		std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution;

		std::vector<Unit*> Enemies;

		BattleScene* battleScene;

	};

	template <typename Derived>
	class derivedEncounterMap : public EncounterMap {

		virtual EncounterMap* clone() {

			Player = new MapPlayer();

			return new Derived(static_cast<Derived const&> (*this));

		}

	};

}