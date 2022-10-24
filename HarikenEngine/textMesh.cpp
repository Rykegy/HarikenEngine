#include "stdafx.h"
#include "textMesh.h"

using namespace HARIKEN;

HARIKEN::textMesh::textMesh(std::vector<vertex> vertices_, GLuint textureID_, GLuint shaderID_) : Mesh(vertices_, textureID_, shaderID_)
{

	deleteTexture = false;

}

HARIKEN::textMesh::~textMesh()
{

}

void HARIKEN::textMesh::render(glm::mat4 transformation_, meshProperties properties_)
{
	
	if(!setup)
		setupMesh();

	glUniform1i(textLoc, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glUseProgram(shaderID);
	if (shaderID == 0)
		return;
	glUniform3f(colorLoc, properties_.color.x, properties_.color.y, properties_.color.z);
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transformation_));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera->getView()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera->getOrthographic()));
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size()); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);

}
