/***********************
Overworld player character.
***********************/

#pragma once
#include "Unit.h"

namespace MEIUN {

	class MapPlayer : public HARIKEN::GameObject
	{
	public:

		void onCreate();
		void update();

		float speed = 5;
		HARIKEN::Collision * collider;
		bool jumpHeld;

	private:

		friend class EncounterMap;
		Unit* unit;

		float iTimer = 0.0f;

	};

}