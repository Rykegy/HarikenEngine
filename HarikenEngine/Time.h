/******************************
Singleton in charge of updating time.
******************************/

#pragma once
#include <SDL.h>
#include <memory>

class Time
{
public:

	Time(const Time&) = delete;
	Time(Time&&) = delete;
	Time& operator = (const Time&) = delete;
	Time& operator = (Time&&) = delete;

	static Time* GetInstance();

	Uint64 timeNow;
	Uint64 timePrev;

	float deltaTime;

	void update();

	void reset();

	void start();

private:
	Time();
	~Time();

	static std::unique_ptr<Time>instance;
	friend std::default_delete<Time>;

	bool rez = true;

};

