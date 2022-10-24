/*******************************************************************************************************
Singleton used to handle input events and can return a true and false for what kind of event it was. Currently not fully mapped.
*******************************************************************************************************/

#pragma once

#include <SDL.h>
#include <memory>
#include "glm.hpp"

namespace HARIKEN {

	struct click {

		bool leftclick = false;
		bool leftclickdown = false;
		bool leftclickup = false;

		bool rightclick = false;
		bool rightclickdown = false;
		bool rightclickup = false;

		glm::vec2 scroll;

		glm::vec2 clickpos;

	};

	struct input {

		click Click;

		bool w = false;
		bool onwdown = false;
		bool onwup = false;

		bool a = false;
		bool onadown = false;
		bool onaup = false;

		bool s = false;
		bool onsdown = false;
		bool onsup = false;

		bool d = false;
		bool onddown = false;
		bool ondup = false;

		bool space = false;
		bool onspacedown = false;
		bool onspaceup = false;

		bool left = false;
		bool onleftdown = false;
		bool onleftup = false;

		bool right = false;
		bool onrightdown = false;
		bool onrightup = false;

		bool up = false;
		bool onupdown = false;
		bool onupup = false;

		bool down = false;
		bool ondowndown = false;
		bool ondownup = false;

		bool enter = false;
		bool onenterdown = false;
		bool onenterup = false;

		bool shift = false;
		bool onshiftdown = false;
		bool onshiftup = false;

		bool p = false;
		bool onpdown = false;
		bool onpup = false;

	};

	class InputSys
	{
	public:

		InputSys(const InputSys&) = delete;
		InputSys(InputSys&&) = delete;
		InputSys& operator = (const InputSys&) = delete;
		InputSys& operator = (InputSys&&) = delete;

		static InputSys* GetInstance();

		bool init();
		void update();
		bool shutdown();

		SDL_Event event;

		input inputs;

	protected:

		bool KMS = false;

	private:

		InputSys();
		~InputSys();

		static std::unique_ptr<InputSys>instance;
		friend std::default_delete<InputSys>;

	};

}