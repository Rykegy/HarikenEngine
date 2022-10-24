#include "stdafx.h"
#include "InputSys.h"

using namespace HARIKEN;

std::unique_ptr<InputSys> InputSys::instance = nullptr;

InputSys::InputSys()
{

}


InputSys::~InputSys()
{
}

InputSys * HARIKEN::InputSys::GetInstance()
{

	if (instance.get() == nullptr)
		instance.reset(new InputSys);

	return instance.get();

}

bool InputSys::init() {

	return true;

}

void InputSys::update()
{
	//Uses the idea of flip flops / latches to determine if keys are being pressed, held down and released. In my experience, this seems to be more reliable than the default methods especially during multi-button inputs.
	if (inputs.onaup)
		inputs.onaup = false;

	if (inputs.ondup)
		inputs.ondup = false;

	if (inputs.onsup)
		inputs.onsup = false;

	if (inputs.onwup)
		inputs.onwup = false;

	if (inputs.onpup)
		inputs.onpup = false;

	if (inputs.onspaceup)
		inputs.onspaceup = false;

	if (inputs.onenterup)
		inputs.onenterup = false;

	if (inputs.onshiftup)
		inputs.onshiftup = false;

	if (inputs.onleftup)
		inputs.onleftup = false;

	if (inputs.onrightup)
		inputs.onrightup = false;

	if (inputs.onupup)
		inputs.onupup = false;

	if (inputs.ondownup)
		inputs.ondownup = false;

	if (inputs.Click.leftclickup)
		inputs.Click.leftclickup = false;

	if (inputs.Click.rightclickup)
		inputs.Click.rightclickup = false;

	inputs.Click.leftclickdown = false;
	inputs.Click.rightclickdown = false;

	int mPosX;
	int mPosY;

	SDL_GetMouseState(&mPosX, &mPosY);

	inputs.Click.clickpos = glm::vec2(mPosX, mPosY);

	while (SDL_PollEvent(&event)) {
		switch (event.type) {

		case SDL_EventType::SDL_QUIT:
			KMS = true;
			return;

		case SDL_EventType::SDL_MOUSEWHEEL:
			inputs.Click.scroll = glm::vec2(event.wheel.x, event.wheel.y);

		case SDL_EventType::SDL_MOUSEBUTTONDOWN:
			switch (event.button.button)
			{
			
			case SDL_BUTTON_LEFT:
				if (!inputs.Click.leftclick)
					inputs.Click.leftclickdown = true;

				inputs.Click.leftclick = true;
				return;

			case SDL_BUTTON_RIGHT:
				if (!inputs.Click.rightclick)
					inputs.Click.rightclickdown = true;

				inputs.Click.rightclick = true;
				return;

			}

		case SDL_EventType::SDL_MOUSEBUTTONUP:
			switch (event.button.button)
			{

			case SDL_BUTTON_LEFT:
				inputs.Click.leftclickup = true;
				inputs.Click.leftclick = false;
				return;

			case SDL_BUTTON_RIGHT:
				inputs.Click.rightclickup = true;
				inputs.Click.rightclick = false;
				return;

			}

		case SDL_EventType::SDL_KEYDOWN:
			switch (event.key.keysym.sym) {

			case SDLK_ESCAPE:
				KMS = true;
				return;

			case SDLK_w:
				if (!inputs.w)
					inputs.onwdown = true;
				else
					inputs.onwdown = false;

				inputs.w = true;
				return;

			case SDLK_a:
				if (!inputs.a)
					inputs.onadown = true;
				else
					inputs.onadown = false;

				inputs.a = true;
				return;

			case SDLK_s:
				if (!inputs.s)
					inputs.onsdown = true;
				else
					inputs.onsdown = false;

				inputs.s = true;
				return;

			case SDLK_d:
				if (!inputs.d)
					inputs.onddown = true;
				else
					inputs.onddown = false;

				inputs.d = true;
				return;

			case SDLK_p:
				if (!inputs.p)
					inputs.onpdown = true;
				else
					inputs.onpdown = false;

				inputs.p = true;
				return;

			case SDLK_SPACE:
				if (!inputs.space)
					inputs.onspacedown = true;
				else
					inputs.onspacedown = false;

				inputs.space = true;
				return;

			case SDLK_RETURN:
				if (!inputs.enter)
					inputs.onenterdown = true;
				else
					inputs.onenterdown = false;

				inputs.enter = true;
				return;

			case SDLK_LSHIFT:
				if (!inputs.shift)
					inputs.onshiftdown = true;
				else
					inputs.onshiftdown = false;

				inputs.shift = true;
				return;

			case SDLK_RSHIFT:
				if (!inputs.shift)
					inputs.onshiftdown = true;
				else
					inputs.onshiftdown = false;

				inputs.shift = true;
				return;

			case SDLK_LEFT:
				if (!inputs.left)
					inputs.onleftdown = true;
				else
					inputs.onleftdown = false;

				inputs.left = true;
				return;

			case SDLK_RIGHT:
				if (!inputs.right)
					inputs.onrightdown = true;
				else
					inputs.onrightdown = false;

				inputs.right = true;
				return;

			case SDLK_UP:
				if (!inputs.up)
					inputs.onupdown = true;
				else
					inputs.onupdown = false;

				inputs.up = true;
				return;

			case SDLK_DOWN:
				if (!inputs.down)
					inputs.ondowndown = true;
				else
					inputs.ondowndown = false;

				inputs.down = true;
				return;

			}

		case SDL_EventType::SDL_KEYUP:
			switch (event.key.keysym.sym) {

			case SDLK_w:
				inputs.onwup = true;
				inputs.w = false;
				inputs.onwdown = false;
				return;

			case SDLK_a:
				inputs.onaup = true;
				inputs.a = false;
				inputs.onadown = false;
				return;

			case SDLK_s:
				inputs.onsup = true;
				inputs.s = false;
				inputs.onsdown = false;
				return;

			case SDLK_d:
				inputs.ondup = true;
				inputs.d = false;
				inputs.onddown = false;
				return;

			case SDLK_p:
				inputs.onpup = true;
				inputs.p = false;
				inputs.onpdown = false;
				return;

			case SDLK_UP:
				inputs.onupup = true;
				inputs.up = false;
				inputs.onupdown = false;
				return;

			case SDLK_DOWN:
				inputs.ondownup = true;
				inputs.down = false;
				inputs.ondowndown = false;
				return;

			case SDLK_LEFT:
				inputs.onleftup = true;
				inputs.left = false;
				inputs.onleftdown = false;
				return;

			case SDLK_RIGHT:
				inputs.onrightup = true;
				inputs.right = false;
				inputs.onrightdown = false;
				return;

			case SDLK_SPACE:
				inputs.onspaceup = true;
				inputs.space = false;
				inputs.onspacedown = false;
				return;

			case SDLK_RETURN:
				inputs.onenterup = true;
				inputs.enter = false;
				inputs.onenterdown = false;
				return;

			case SDLK_LSHIFT:
				inputs.onshiftup = true;
				inputs.shift = false;
				inputs.onshiftdown = false;
				return;

			case SDLK_RSHIFT:
				inputs.onshiftup = true;
				inputs.shift = false;
				inputs.onshiftdown = false;
				return;

			}

		default:
			return;
		}
	}

}

bool InputSys::shutdown()
{

	if (KMS)
		return true;

	return false;
}
