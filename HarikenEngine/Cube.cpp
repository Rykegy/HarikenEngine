#include "stdafx.h"
#include "Cube.h"

using namespace HARIKEN;

void HARIKEN::Cube::onCreate()
{

	TextureHandler::GetInstance()->createTexture("checker", "IMG/TextureTest/2000px-Checkerboard_pattern[1].png");
	ShaderHandler::GetInstance()->createShader("lightTexture", "Shaders/Light");
	
	shape = new cubeModel(TextureHandler::GetInstance()->getTexture("checker"), ShaderHandler::GetInstance()->getShader("lightTexture"));
	shape->setPosition(glm::vec3(0.0f, 0.0f, -5.0f));
	shape->setScale(glm::vec3(1.0f));

	model.push_back(shape);

}
#include <iostream>
void HARIKEN::Cube::update()
{
	
	//std::cout << Camera::GetInstance()->getLightSources()[0]->GetPosition().x << ", " << Camera::GetInstance()->getLightSources()[0]->GetPosition().y << ", " << Camera::GetInstance()->getLightSources()[0]->GetPosition().z << std::endl;

	for (auto m : model) {

		m->setRotation(glm::vec3(1.0f, 1.0f, 1.0f));
		m->setAngle(angle);

		angle += time->deltaTime;
		if (angle > 360.0f)
			angle -= 360;

	}

}
