// HarikenEngine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Engine.h"
#include <ctime>

using namespace HARIKEN;

int main(int argc, char* argv[])
{

	srand(static_cast <unsigned> (time(0)));

	Engine* engine = Engine::startEngine();

	engine->init();
	engine->Run();

    return 0;

}