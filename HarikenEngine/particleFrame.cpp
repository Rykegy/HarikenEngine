#include "stdafx.h"
#include "particleFrame.h"

using namespace HARIKEN;

particleFrame::particleFrame()
{

	vertex v;
	std::vector<vertex> vertices;

	v.position = glm::vec3(0.0f, 0.0f, 0.0f);
	v.color = glm::vec3(0.0f, 0.0f, 0.0f);
	vertices.push_back(v);

	v.position = glm::vec3(0.0f, 0.0f, 0.0f);
	v.color = glm::vec3(0.0f, 0.0f, 0.0f);
	vertices.push_back(v);

	v.position = glm::vec3(0.0f, 0.0f, 0.0f);
	v.color = glm::vec3(0.0f, 0.0f, 0.0f);
	vertices.push_back(v);

	addMesh(new Mesh(vertices, 0, 0));

	v.position = glm::vec3(0.0f, 0.0f, 0.0f);
	v.color = glm::vec3(0.0f, 0.0f, 0.0f);
	vertices.push_back(v);

	v.position = glm::vec3(0.0f, 0.0f, 0.0f);
	v.color = glm::vec3(0.0f, 0.0f, 0.0f);
	vertices.push_back(v);

	v.position = glm::vec3(0.0f, 0.0f, 0.0f);
	v.color = glm::vec3(0.0f, 0.0f, 0.0f);
	vertices.push_back(v);

	addMesh(new Mesh(vertices, 0, 0));

}


particleFrame::~particleFrame()
{
}

HARIKEN::particleFrame::particleFrame(float width, float height, GLuint textureID_)
{
	
	if (GLuint shaderID = ShaderHandler::GetInstance()->getShader("particle") == 0)
		ShaderHandler::GetInstance()->createShader("particle", "Particle");

	GLuint shaderID = ShaderHandler::GetInstance()->getShader("particle");

	vertex v;
	std::vector<vertex> vertices;

	v.position = glm::vec3(-width / 2, height / 2, 0.0f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.texture = glm::vec2(0.0f, 1.0f);
	vertices.push_back(v);

	v.position = glm::vec3(width / 2, height / 2, 0.0f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.texture = glm::vec2(1.0f, 1.0f);
	vertices.push_back(v);

	v.position = glm::vec3(-width / 2, -height / 2, 0.0f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.texture = glm::vec2(0.0f, 0.0f);
	vertices.push_back(v);

	v.position = glm::vec3(width / 2, height / 2, 0.0f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.texture = glm::vec2(1.0f, 1.0f);
	vertices.push_back(v);

	v.position = glm::vec3(width / 2, -height / 2, 0.0f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.texture = glm::vec2(1.0f, 0.0f);
	vertices.push_back(v);

	v.position = glm::vec3(-width / 2, -height / 2, 0.0f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.texture = glm::vec2(0.0f, 0.0f);
	vertices.push_back(v);

	addMesh(new Mesh(vertices, textureID_, shaderID));

}

HARIKEN::particleFrame::particleFrame(float width, float height, GLuint textureID_, glm::vec3 color_)
{

	if (GLuint shaderID = ShaderHandler::GetInstance()->getShader("particle") == 0)
		ShaderHandler::GetInstance()->createShader("particle", "Particle");

	GLuint shaderID = ShaderHandler::GetInstance()->getShader("particle");

	vertex v;
	std::vector<vertex> vertices;

	v.position = glm::vec3(-width / 2, height / 2, 0.0f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.texture = glm::vec2(0.0f, 1.0f);
	v.color = color_;
	vertices.push_back(v);

	v.position = glm::vec3(width / 2, height / 2, 0.0f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.texture = glm::vec2(1.0f, 1.0f);
	v.color = color_;
	vertices.push_back(v);

	v.position = glm::vec3(-width / 2, -height / 2, 0.0f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.texture = glm::vec2(0.0f, 0.0f);
	v.color = color_;
	vertices.push_back(v);

	v.position = glm::vec3(width / 2, height / 2, 0.0f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.texture = glm::vec2(1.0f, 1.0f);
	v.color = color_;
	vertices.push_back(v);

	v.position = glm::vec3(width / 2, -height / 2, 0.0f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.texture = glm::vec2(1.0f, 0.0f);
	v.color = color_;
	vertices.push_back(v);

	v.position = glm::vec3(-width / 2, -height / 2, 0.0f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.texture = glm::vec2(0.0f, 0.0f);
	v.color = color_;
	vertices.push_back(v);

	addMesh(new Mesh(vertices, textureID_, shaderID));

}
