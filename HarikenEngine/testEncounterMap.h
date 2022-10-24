#pragma once
#include "EncounterMap.h"

namespace MEIUN {

	class testEncounterMap : public derivedEncounterMap<testEncounterMap>
	{
	public:

		void onCreate();
		void onStart();

		std::string getName() {

			return "Test EncounterMap";

		}

	private:

		HARIKEN::GameObject * platform0;
		HARIKEN::GameObject * platform1;
		HARIKEN::GameObject * platform2;
		HARIKEN::GameObject * platform3;

		HARIKEN::GameObject * TriggerPoint;

	};

}