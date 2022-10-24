#include "stdafx.h"
#include "Time.h"


std::unique_ptr<Time> Time::instance = nullptr;

Time::Time()
{

	timePrev = SDL_GetTicks();
	timeNow = SDL_GetTicks();

}


Time::~Time()
{
}

Time * Time::GetInstance()
{

	if (instance.get() == nullptr)
		instance.reset(new Time);

	return instance.get();

}

void Time::update()
{

		timePrev = timeNow;
		timeNow = SDL_GetTicks();

		if (rez) {
			deltaTime = 0.0f;
		}
		else
			deltaTime = static_cast<float>(timeNow - timePrev) / 1000.0f;
		//Makes sure that delta time doesn't fall below 60FPS threshold so that when game updates below threshold, physics behavior will continue to act as if the game is working at 60FPS
		if (deltaTime > 1.0f / 60.0f)
			deltaTime = 1.0f / 60.0f;

}

void Time::reset()
{

	rez = true;

}

void Time::start()
{

	rez = false;

}
