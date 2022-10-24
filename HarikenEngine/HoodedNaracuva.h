/*******************
Tutorial boss unit data.
*******************/

#pragma once
#include "Unit.h"

namespace MEIUN {

	class HoodedNaracuva : public derivedUnit<HoodedNaracuva>
	{
	public:

		void onCreate();
		void update();

		void Attack();

	private:

		HARIKEN::Sound* Hahaha;
		HARIKEN::Sound* ShortGrunt;

	};

}