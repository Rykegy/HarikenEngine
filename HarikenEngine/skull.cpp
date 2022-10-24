#include "stdafx.h"
#include "skull.h"

using namespace HARIKEN;

void HARIKEN::skull::onCreate()
{

	objLoader obj("OBJ/skullSmooth.obj");

	/// Create a shader with attributes
	ShaderHandler::GetInstance()->createShader("toon", "classToon");

	model.push_back(new Model());

	for(size_t i = 0; i < obj.verticesList.size(); i++)
		model[0]->addMesh(new Mesh(obj.verticesList[i], 0, ShaderHandler::GetInstance()->getShader("toon")));

	//model[0]->addMesh(new Mesh(obj.vertices, 0, ShaderHandler::GetInstance()->getShader("toon")));
	//model[0]->setPosition(glm::vec3(0.0f, 0.0f, -5.0f));
	setPos(0.0f, 0.0f, -5.0f);

}

void HARIKEN::skull::update()
{
	
	for (auto m : model) {

		m->setRotation(glm::vec3(0.0f, 1.0f, 0.0f));
		m->setAngle(angle);

		angle += time->deltaTime;
		if (angle > 360.0f)
			angle -= 360;

	}
	
}
