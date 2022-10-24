/**********
Title Scene.
**********/

#pragma once
#include "Scene.h"

namespace MEIUN {

	class TitleScreen : public HARIKEN::derivedScene<TitleScreen>
	{
	public:

		void onCreate();
		void onStart();

		std::string getName() {

			return "Title Screen";

		}

		HARIKEN::GameObject* titlepic;

		HARIKEN::UIObject* title;
		HARIKEN::UIObject* startbutt;
		HARIKEN::UIObject* quitbutt;
		HARIKEN::UIObject* languageBar;

	};

}