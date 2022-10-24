#include "stdafx.h"
#include "imageFrame.h"
#include "textMesh.h"

using namespace HARIKEN;
//Create a blank square that has no area.
imageFrame::imageFrame() : Model()
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
//Create a 2D rectangular frame using a given texture
imageFrame::imageFrame(float width, float height, GLuint textureID)
{

	size = glm::vec3(width, height, 0.0f);

	if(ShaderHandler::GetInstance()->getShader("texture") == 0)
		ShaderHandler::GetInstance()->createShader("texture", "ClassText");

	GLuint shaderID = ShaderHandler::GetInstance()->getShader("texture");
	shaderProgram = shaderID;
	//std::cout << ShaderHandler::GetInstance()->getShader("texture") << std::endl;
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

	addMesh(new Mesh(vertices, textureID, shaderID));

}
//Special constructor used to creating frames to display text
HARIKEN::imageFrame::imageFrame(float width, float height, GLuint textureID_, bool isText_)
{

	isText = isText_;

	size = glm::vec3(width, height, 0.0f);

	GLuint shaderID;

	if (isText) {

		if (ShaderHandler::GetInstance()->getShader("font") == 0)
			ShaderHandler::GetInstance()->createShader("font", "font");

		shaderID = ShaderHandler::GetInstance()->getShader("font");

	}

	else {

		if (ShaderHandler::GetInstance()->getShader("texture") == 0)
			ShaderHandler::GetInstance()->createShader("texture", "ClassText");

		shaderID = ShaderHandler::GetInstance()->getShader("texture");

	}

	shaderProgram = shaderID;
	//std::cout << ShaderHandler::GetInstance()->getShader("texture") << std::endl;
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

imageFrame::~imageFrame()
{


}

glm::vec3 HARIKEN::imageFrame::getSize()
{
	return size;
}

void HARIKEN::imageFrame::render()
{

	if (!isText)
		Model::render();

	else {

		for (auto m : subMeshes)
			static_cast<textMesh*>(m)->render(getTransform(), properties);

	}

}
