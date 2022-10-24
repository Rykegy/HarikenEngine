#include "stdafx.h"
#include "Dice.h"
#include "WindowSys.h"

using namespace HARIKEN;

void HARIKEN::Dice::onCreate()
{

	objLoader obj("OBJ/Dice.obj");
	mtlLoader mtl("MAT/Dice.mtl");

	TextureHandler::GetInstance()->createTexture("dice", "IMG/TextureTest/diceMap.jpg");
	ShaderHandler::GetInstance()->createShader("leight", "Shaders/Light");

	model.push_back(new Model());
	
	model[0]->addMesh(new Mesh(obj.verticesList[0], TextureHandler::GetInstance()->getTexture("dice"), mtl.mtlList[0]));
	model[0]->setPosition(glm::vec3(2.0f, 0.0f, -5.0f));

	collider = new BoundingCollider(model[0]);
	//collider = new CircleCollider(0.5, 0, 0);

	modelBound.push_back(BoundingCollider(model[0]));

}

void HARIKEN::Dice::update()
{

	glm::vec2 windowSize = Window->getWinSize();

	if (getMouseState() != "") {

		if (getMouseState() == "LEFTDOWN") {

			glm::vec2 mousePos(getMousePosition().x / windowSize.x * 2 - 1, getMousePosition().y / windowSize.y * 2 - 1);

			glm::vec3 a(getMousePosition().x, getMousePosition().y, 0);
			glm::vec3 b(getMousePosition().x, getMousePosition().y, -1);

			glm::vec3 result = glm::unProject(a, Camera::GetInstance()->getView(), Camera::GetInstance()->getPerspective(), glm::vec4(0.0f, 0.0f, float(windowSize.x), float(windowSize.y)));
			glm::vec3 result2 = glm::unProject(b, Camera::GetInstance()->getView(), Camera::GetInstance()->getPerspective(), glm::vec4(0.0f, 0.0f, float(windowSize.x), float(windowSize.y)));

			result.y *= -1;
			result2.y *= -1;

			glm::vec3 pickingPos = result;
			glm::vec3 pickingDir = result2 - result;
			pickingDir.x /= pickingDir.z;
			pickingDir.y /= pickingDir.z;
			pickingDir.z /= pickingDir.z;

			bool somethingInfront = false;

			std::vector<glm::vec2> modelScreenCoord = getModelBoxScreenCoord();

			//std::cout << "Min X: " << modelScreenCoord[0].x << ", Min Y: " << modelScreenCoord[0].y << std::endl << "Max X: " << modelScreenCoord[1].x << ", Max Y: " << modelScreenCoord[1].y << std::endl;

			if (getMousePosition().x >= modelScreenCoord[0].x && getMousePosition().x <= modelScreenCoord[1].x)
				if (getMousePosition().y >= modelScreenCoord[0].y && getMousePosition().y <= modelScreenCoord[1].y)
					std::cout << "Dice" << std::endl;

		}

	}
	/*
	for (auto m : model) {

		m->setRotation(glm::vec3(0.0f, 1.0f, 0.0f));
		m->setAngle(angle);

		angle += deltaTime;
		if (angle > 360.0f)
			angle -= 360;

	}
	*/
}
