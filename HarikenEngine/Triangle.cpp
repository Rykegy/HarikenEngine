#include "stdafx.h"
#include "Triangle.h"

using namespace HARIKEN;

Triangle::Triangle() : Model()
{

	if (ShaderHandler::GetInstance()->getShader("Triangle") == 0)
		ShaderHandler::GetInstance()->createShader("Triangle", "Tri");

	GLuint shaderID = ShaderHandler::GetInstance()->getShader("Triangle");

	vertex v;
	std::vector<vertex> vertices;

	v.position = glm::vec3(0.0f, 0.5f, 0.0f);
	v.color = glm::vec3(0.0f, 0.0f, 1.0f);
	vertices.push_back(v);

	v.position = glm::vec3(-0.5f, -0.5f, 0.0f);
	v.color = glm::vec3(0.0f, 1.0f, 0.0f);
	vertices.push_back(v);

	v.position = glm::vec3(0.5f, -0.5f, 0.0f);
	v.color = glm::vec3(1.0f, 0.0f, 0.0f);
	vertices.push_back(v);

	addMesh(new Mesh(vertices, 0, shaderID));

}


Triangle::~Triangle()
{
}

