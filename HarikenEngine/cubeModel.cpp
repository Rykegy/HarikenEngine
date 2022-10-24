#include "stdafx.h"
#include "cubeModel.h"

using namespace HARIKEN;

cubeModel::cubeModel(GLuint textureID_, GLuint shaderID_) : Model()
{

	vertex v;
	std::vector<vertex> vertexList;
	v.position = glm::vec3(-1.0f, -1.0f, -1.0f);
	v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
	v.texture = glm::vec2(0.0f, 0.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(1.0f, -1.0f, -1.0f);
	v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
	v.texture = glm::vec2(1.0f, 0.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(1.0f, 1.0f, -1.0f);
	v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
	v.texture = glm::vec2(1.0f, 1.0f);
	vertexList.push_back(v);

	v.position = glm::vec3(1.0f, 1.0f, -1.0f);
	v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
	v.texture = glm::vec2(1.0f, 1.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(-1.0f, 1.0f, -1.0f);
	v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
	v.texture = glm::vec2(0.0f, 1.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(-1.0f, -1.0f, -1.0f);
	v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
	v.texture = glm::vec2(0.0f, 0.0f);
	vertexList.push_back(v);
	addMesh(new Mesh(vertexList, textureID_, shaderID_));

	vertexList.clear();
	vertexList.shrink_to_fit();

	v.position = glm::vec3(-1.0f, -1.0f, 1.0f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.texture = glm::vec2(0.0f, 0.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(1.0f, -1.0f, 1.0f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.texture = glm::vec2(1.0f, 0.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(1.0f, 1.0f, 1.0f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.texture = glm::vec2(1.0f, 1.0f);
	vertexList.push_back(v);

	v.position = glm::vec3(1.0f, 1.0f, 1.0f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.texture = glm::vec2(1.0f, 1.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(-1.0f, 1.0f, 1.0f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.texture = glm::vec2(0.0f, 1.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(-1.0f, -1.0f, 1.0f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.texture = glm::vec2(0.0f, 0.0f);
	vertexList.push_back(v);
	addMesh(new Mesh(vertexList, textureID_, shaderID_));

	vertexList.clear();
	vertexList.shrink_to_fit();

	v.position = glm::vec3(-1.0f, 1.0f, 1.0f);
	v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	v.texture = glm::vec2(0.0f, 0.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(-1.0f, 1.0f, -1.0f);
	v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	v.texture = glm::vec2(1.0f, 0.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(-1.0f, -1.0f, -1.0f);
	v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	v.texture = glm::vec2(1.0f, 1.0f);
	vertexList.push_back(v);

	v.position = glm::vec3(-1.0f, -1.0f, -1.0f);
	v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	v.texture = glm::vec2(1.0f, 1.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(-1.0f, -1.0f, 1.0f);
	v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	v.texture = glm::vec2(0.0f, 1.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(-1.0f, 1.0f, 1.0f);
	v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	v.texture = glm::vec2(0.0f, 0.0f);
	vertexList.push_back(v);
	addMesh(new Mesh(vertexList, textureID_, shaderID_));

	vertexList.clear();
	vertexList.shrink_to_fit();

	v.position = glm::vec3(1.0f, 1.0f, 1.0f);
	v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
	v.texture = glm::vec2(0.0f, 0.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(1.0f, 1.0f, -1.0f);
	v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
	v.texture = glm::vec2(1.0f, 0.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(1.0f, -1.0f, -1.0f);
	v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
	v.texture = glm::vec2(1.0f, 1.0f);
	vertexList.push_back(v);

	v.position = glm::vec3(1.0f, -1.0f, -1.0f);
	v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
	v.texture = glm::vec2(1.0f, 1.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(1.0f, -1.0f, 1.0f);
	v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
	v.texture = glm::vec2(0.0f, 1.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(1.0f, 1.0f, 1.0f);
	v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
	v.texture = glm::vec2(0.0f, 0.0f);
	vertexList.push_back(v);
	addMesh(new Mesh(vertexList, textureID_, shaderID_));

	vertexList.clear();
	vertexList.shrink_to_fit();

	v.position = glm::vec3(-1.0f, -1.0f, -1.0f);
	v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
	v.texture = glm::vec2(0.0f, 0.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(1.0f, -1.0f, -1.0f);
	v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
	v.texture = glm::vec2(1.0f, 0.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(1.0f, -1.0f, 1.0f);
	v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
	v.texture = glm::vec2(1.0f, 1.0f);
	vertexList.push_back(v);

	v.position = glm::vec3(1.0f, -1.0f, 1.0f);
	v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
	v.texture = glm::vec2(1.0f, 1.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(-1.0f, -1.0f, 1.0f);
	v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
	v.texture = glm::vec2(0.0f, 1.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(-1.0f, -1.0f, -1.0f);
	v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
	v.texture = glm::vec2(0.0f, 0.0f);
	vertexList.push_back(v);
	addMesh(new Mesh(vertexList, textureID_, shaderID_));

	vertexList.clear();
	vertexList.shrink_to_fit();

	v.position = glm::vec3(-1.0f, 1.0f, -1.0f);
	v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
	v.texture = glm::vec2(0.0f, 0.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(1.0f, 1.0f, -1.0f);
	v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
	v.texture = glm::vec2(1.0f, 0.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(1.0f, 1.0f, 1.0f);
	v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
	v.texture = glm::vec2(1.0f, 1.0f);
	vertexList.push_back(v);

	v.position = glm::vec3(1.0f, 1.0f, 1.0f);
	v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
	v.texture = glm::vec2(1.0f, 1.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(-1.0f, 1.0f, 1.0f);
	v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
	v.texture = glm::vec2(0.0f, 1.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(-1.0f, 1.0f, -1.0f);
	v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
	v.texture = glm::vec2(0.0f, 0.0f);
	vertexList.push_back(v);
	addMesh(new Mesh(vertexList, textureID_, shaderID_));

	vertexList.clear();
	vertexList.shrink_to_fit();

}


cubeModel::~cubeModel()
{
}
