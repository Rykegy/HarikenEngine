#pragma once
#include "UIObject.h"

namespace HARIKEN {

	class LoadingLoad : public UIObject
	{

	public:

		void onCreate();

		void update();

	private:

		const Texture* en;
		const Texture* jp;

		Language ln;

	};

}