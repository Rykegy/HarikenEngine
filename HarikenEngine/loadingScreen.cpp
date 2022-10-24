#include "stdafx.h"
#include "loadingScreen.h"
#include "LoadingLoad.h"
#include "LoadingPoint.h"

#include <string>

using namespace HARIKEN;

std::vector<LoadingPoint*> loadPoints;
std::vector < glm::vec2> ogPos;

float* deltaTime;

double piPhase;

void HARIKEN::loadingScreen::onCreate()
{

	bgColor = glm::vec3(0.9f, 0.9f, 0.9f);

	deltaTime = &Time::GetInstance()->deltaTime;

	LoadingLoad* loadImg = new LoadingLoad();

	loadImg->alignment.horizontal = UIObject::Align::right;
	loadImg->setPosition(windowSize.x - 150.0f, 50.0f);

	addUI(loadImg, "LoadImg");

	glm::vec2 pos = loadImg->getPosition();

	for (int i = 0; i < 5; i++) {

		LoadingPoint* loadPoint = new LoadingPoint();
		loadPoint->alignment.horizontal = UIObject::Align::left;
		loadPoint->setPosition(pos + glm::vec2(i * 20 - 1.0f, 0.0f));

		addUI(loadPoint, "LoadPoint" + std::to_string(i));
		loadPoints.push_back(loadPoint);
		ogPos.push_back(loadPoint->getPosition());

	}

}

void HARIKEN::loadingScreen::onStart()
{

	piPhase = 0.0f;

}

void HARIKEN::loadingScreen::shutdown()
{
}

void HARIKEN::loadingScreen::update()
{

	if (loadingThreads == nullptr || allThreadsDone) {

		allThreadsDone = true;
		return;

	}
	//Check if all the threads have finished.
	for (size_t i = 0; i < loadingThreads->size(); i++) {

		if (loadingThreads->at(i)->wait_for(std::chrono::milliseconds(10)) == std::future_status::ready) {

			loadingThreads->erase(loadingThreads->begin() + i);

		}

	}

	if (loadingThreads->empty())
		allThreadsDone = true;

	for (size_t i = 0; i < loadPoints.size(); i++) {

		double phaseShift = std::_Pi * (4 - i) / 5;
		float factor = sin(piPhase + phaseShift + std::_Pi);

		if (factor >= 0) {
			loadPoints[i]->setPosition(ogPos[i] + glm::vec2(0.0f, 50.0 * factor));
		}

		else
			loadPoints[i]->setPosition(ogPos[i]);

	}

	piPhase += std::_Pi * *deltaTime;

	if (piPhase > 2 * std::_Pi)
		piPhase -= 2 * std::_Pi;

}

void HARIKEN::loadingScreen::startLoading(std::vector<std::future<void>*>* loadingThreads_) //Set the reference to the threads used for loading to determine when loading is finished
{

	loadingThreads = loadingThreads_;

	allThreadsDone = false;

}
