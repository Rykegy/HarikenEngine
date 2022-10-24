#include "stdafx.h"
#include "Apple.h"
#include "WindowSys.h"

void HARIKEN::Apple::onCreate()
{

	objLoader obj("OBJ/Apple.obj");
	mtlLoader mtl("MAT/Apple.mtl");

	TextureHandler::GetInstance()->createTexture("appleBody", "IMG/TextureTest/Apple_Body.JPG");
	TextureHandler::GetInstance()->createTexture("appleStem", "IMG/TextureTest/Apple_Branch.JPG");
	ShaderHandler::GetInstance()->createShader("leight", "Shaders/Light");

	model.push_back(new Model());
	model[0]->addMesh(new Mesh(obj.verticesList[0], TextureHandler::GetInstance()->getTexture("appleBody"), mtl.mtlList[0]));
	model[0]->addMesh(new Mesh(obj.verticesList[1], TextureHandler::GetInstance()->getTexture("appleStem"), mtl.mtlList[1]));
	model[0]->setPosition(glm::vec3(-2.0f, -2.0f, -5.0f));

	modelBound.push_back(BoundingCollider(model[0]));

}
#include<matrix.hpp>
void HARIKEN::Apple::update()
{

	if (getMouseState() != "") {

		if (getMouseState() == "LEFTDOWN") {

			glm::vec2 windowSize = Window->getWinSize();

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
			/*
			bool somethingInfront = false;

			for (auto sceneObj : currentScene->objects)
				if (!sceneObj->model.empty())
					if (pickingDir.x * sceneObj->model[0]->getPosition().z <= static_cast<BoundingCollider*>(collider)->maxX + sceneObj->model[0]->getPosition().x && pickingDir.x * sceneObj->model[0]->getPosition().z >= static_cast<BoundingCollider*>(collider)->minX + sceneObj->model[0]->getPosition().x)
						if (pickingDir.y * sceneObj->model[0]->getPosition().z <= static_cast<BoundingCollider*>(collider)->maxY + sceneObj->model[0]->getPosition().y && pickingDir.y * sceneObj->model[0]->getPosition().z >= static_cast<BoundingCollider*>(collider)->minY + sceneObj->model[0]->getPosition().y)
							somethingInfront = true;

			if (!somethingInfront)*/
			/*
			if (pickingDir.x * model[0]->getPosition().z <= static_cast<BoundingCollider*>(collider)->maxX + model[0]->getPosition().x && pickingDir.x * model[0]->getPosition().z >= static_cast<BoundingCollider*>(collider)->minX + model[0]->getPosition().x)
				if (pickingDir.y * model[0]->getPosition().z <= static_cast<BoundingCollider*>(collider)->maxY + model[0]->getPosition().y && pickingDir.y * model[0]->getPosition().z >= static_cast<BoundingCollider*>(collider)->minY + model[0]->getPosition().y)
					std::cout << "Apple" << std::endl;*/
			/*
			if (pickingDir.x * (static_cast<BoundingCollider*>(collider)->minZ + model[0]->getPosition().z) <= static_cast<BoundingCollider*>(collider)->maxX + model[0]->getPosition().x && pickingDir.x * (static_cast<BoundingCollider*>(collider)->minZ + model[0]->getPosition().z) >= static_cast<BoundingCollider*>(collider)->minX + model[0]->getPosition().x)
				if (pickingDir.y * (static_cast<BoundingCollider*>(collider)->minZ + model[0]->getPosition().z) <= static_cast<BoundingCollider*>(collider)->maxY + model[0]->getPosition().y && pickingDir.y * (static_cast<BoundingCollider*>(collider)->minZ + model[0]->getPosition().z) >= static_cast<BoundingCollider*>(collider)->minY + model[0]->getPosition().y)
					std::cout << "Apple" << std::endl;
					*/

			//std::cout << getMousePosition().x << ", " << getMousePosition().y << std::endl;

			std::vector<glm::vec2> modelScreenCoord = getModelBoxScreenCoord();

			//std::cout << "Min X: " << modelScreenCoord[0].x << ", Min Y: " << modelScreenCoord[0].y << std::endl << "Max X: " << modelScreenCoord[1].x << ", Max Y: " << modelScreenCoord[1].y << std::endl;
			if (getMousePosition().x >= modelScreenCoord[0].x && getMousePosition().x <= modelScreenCoord[1].x)
				if (getMousePosition().y >= modelScreenCoord[0].y && getMousePosition().y <= modelScreenCoord[1].y)
					std::cout << "Apple" << std::endl << modelScreenCoord[2].x << ", " << modelScreenCoord[2].y << std::endl;

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
