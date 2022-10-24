#include "stdafx.h"
#include "Mesh.h"
#include "SceneManager.h"

using namespace HARIKEN;

HARIKEN::Mesh::Mesh(std::vector<vertex> vertices_)
{
	vao = 0;
	vbo = 0;
	vertices = vertices_;
}

HARIKEN::Mesh::Mesh(std::vector<vertex> vertices_, GLuint textureID_, mtl mat)
{

	textureID = textureID_;

	vao = 0;
	vbo = 0;
	vertices = vertices_;
	Mat = mat;

	ShaderHandler::GetInstance()->createShader("materialShader", "material");
	shaderID = ShaderHandler::GetInstance()->getShader("materialShader");

}

Mesh::Mesh(std::vector<vertex> vertices_, GLuint textureID_, GLuint shaderID_)
{

	textureID = textureID_;

	vao = 0;
	vbo = 0;
	vertices = vertices_;

	shaderID = shaderID_;

}


Mesh::~Mesh()
{

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);

}

GLuint HARIKEN::Mesh::getTextureID()
{
	return textureID;
}

void Mesh::setupMesh() {

	setup = true;

	camera = Camera::GetInstance();
	twoD = SceneManager::GetInstance()->currentScene->twoD;
	//twoD = true;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	for (size_t i = 0; i < vertices.size(); i++) {

		g_vertex_buffer_data.push_back(vertices[i].position.x);
		g_vertex_buffer_data.push_back(vertices[i].position.y);
		g_vertex_buffer_data.push_back(vertices[i].position.z);

	}

	for (size_t i = 0; i < vertices.size(); i++) {

		g_normal_buffer_data.push_back(vertices[i].normal.x);
		g_normal_buffer_data.push_back(vertices[i].normal.y);
		g_normal_buffer_data.push_back(vertices[i].normal.z);

	}

	for (size_t i = 0; i < vertices.size(); i++) {

		g_texture_buffer_data.push_back(vertices[i].texture.x);
		g_texture_buffer_data.push_back(vertices[i].texture.y);

	}

	for (size_t i = 0; i < vertices.size(); i++) {

		g_color_buffer_data.push_back(vertices[i].color.x);
		g_color_buffer_data.push_back(vertices[i].color.y);
		g_color_buffer_data.push_back(vertices[i].color.z);

	}

#define VERTBUFFERSIZE (g_vertex_buffer_data.size() * sizeof(GLfloat))
#define NORMBUFFERSIZE (g_normal_buffer_data.size() * sizeof(GLfloat))
#define TEXTBUFFERSIZE (g_texture_buffer_data.size() * sizeof(GLfloat))
#define COLOBUFFERSIZE (g_color_buffer_data.size() * sizeof(GLfloat))

	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vbo);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, VERTBUFFERSIZE + NORMBUFFERSIZE + TEXTBUFFERSIZE + COLOBUFFERSIZE, NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, VERTBUFFERSIZE, &g_vertex_buffer_data[0]);
	glBufferSubData(GL_ARRAY_BUFFER, VERTBUFFERSIZE, NORMBUFFERSIZE, &g_normal_buffer_data[0]);
	glBufferSubData(GL_ARRAY_BUFFER, VERTBUFFERSIZE + NORMBUFFERSIZE, TEXTBUFFERSIZE, &g_texture_buffer_data[0]);
	glBufferSubData(GL_ARRAY_BUFFER, VERTBUFFERSIZE + NORMBUFFERSIZE + TEXTBUFFERSIZE, COLOBUFFERSIZE, &g_color_buffer_data[0]);

	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,                  // VerticesID
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,                  // NormalID
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,					// stride
		(void*)VERTBUFFERSIZE
	);

	// 3rd attribute buffer : textures
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(
		2,                  // TextureID
		2,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)(VERTBUFFERSIZE + NORMBUFFERSIZE)
	);

	// 4th attribute buffer : color
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(
		3,                  // ColorID
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)(VERTBUFFERSIZE + NORMBUFFERSIZE + TEXTBUFFERSIZE)
	);

	glBindBuffer(GL_ARRAY_BUFFER, 0); /// Unbinds the buffer by setting it to zero   
	glBindVertexArray(0); // Disable the VBO  
	glEnableVertexAttribArray(0); // Disable the VAO

	modelLoc = glGetUniformLocation(shaderID, "model");
	viewLoc = glGetUniformLocation(shaderID, "view");
	projLoc = glGetUniformLocation(shaderID, "proj");
	textLoc = glGetUniformLocation(shaderID, "inputTexture");
	brightLoc = glGetUniformLocation(shaderID, "brightness");
	opaqueLoc = glGetUniformLocation(shaderID, "opaqueness");
	colorLoc = glGetUniformLocation(shaderID, "myColor");
	particleLightColLoc = glGetUniformLocation(shaderID, "lightColor");
	viewPosLoc = glGetUniformLocation(shaderID, "viewPosition");
	lightPosLoc = glGetUniformLocation(shaderID, "light.pos");
	lightAmbLoc = glGetUniformLocation(shaderID, "light.ambient");
	lightDiffLoc = glGetUniformLocation(shaderID, "light.diffuse");
	lightColLoc = glGetUniformLocation(shaderID, "light.color");

#undef VERTBUFFERSIZE
#undef NORMBUFFERSIZE
#undef TEXTBUFFERSIZE
#undef COLOBUFFERSIZE


}

void HARIKEN::Mesh::setupMeshMat()
{

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	for (size_t i = 0; i < vertices.size(); i++) {

		g_vertex_buffer_data.push_back(vertices[i].position.x);
		g_vertex_buffer_data.push_back(vertices[i].position.y);
		g_vertex_buffer_data.push_back(vertices[i].position.z);

	}

	for (size_t i = 0; i < vertices.size(); i++) {

		g_normal_buffer_data.push_back(vertices[i].normal.x);
		g_normal_buffer_data.push_back(vertices[i].normal.y);
		g_normal_buffer_data.push_back(vertices[i].normal.z);

	}

	for (size_t i = 0; i < vertices.size(); i++) {

		g_texture_buffer_data.push_back(vertices[i].texture.x);
		g_texture_buffer_data.push_back(vertices[i].texture.y);

	}

	for (size_t i = 0; i < vertices.size(); i++) {

		g_color_buffer_data.push_back(vertices[i].color.x);
		g_color_buffer_data.push_back(vertices[i].color.y);
		g_color_buffer_data.push_back(vertices[i].color.z);

	}

#define VERTBUFFERSIZE (g_vertex_buffer_data.size() * sizeof(GLfloat))
#define NORMBUFFERSIZE (g_normal_buffer_data.size() * sizeof(GLfloat))
#define TEXTBUFFERSIZE (g_texture_buffer_data.size() * sizeof(GLfloat))
#define COLOBUFFERSIZE (g_color_buffer_data.size() * sizeof(GLfloat))

#define DIFFMAPBUFFERSIZE (sizeof(GLint))
#define NSBUFFERSIZE (sizeof(GLfloat))
#define NIBUFFERSIZE (sizeof(GLfloat))
#define DBUFFERSIZE (sizeof(GLfloat))
#define TRBUFFERSIZE (sizeof(GLfloat))

#define TFBUFFERSIZE (3 * sizeof(GLfloat))
#define KABUFFERSIZE (3 * sizeof(GLfloat))
#define KDBUFFERSIZE (3 * sizeof(GLfloat))
#define KSBUFFERSIZE (3* sizeof(GLfloat))
#define KEBUFFERSIZE (3* sizeof(GLfloat))

	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vbo);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, VERTBUFFERSIZE + NORMBUFFERSIZE + TEXTBUFFERSIZE + COLOBUFFERSIZE, NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, VERTBUFFERSIZE, &g_vertex_buffer_data[0]);
	glBufferSubData(GL_ARRAY_BUFFER, VERTBUFFERSIZE, NORMBUFFERSIZE, &g_normal_buffer_data[0]);
	glBufferSubData(GL_ARRAY_BUFFER, VERTBUFFERSIZE + NORMBUFFERSIZE, TEXTBUFFERSIZE, &g_texture_buffer_data[0]);
	glBufferSubData(GL_ARRAY_BUFFER, VERTBUFFERSIZE + NORMBUFFERSIZE + TEXTBUFFERSIZE, COLOBUFFERSIZE, &g_color_buffer_data[0]);
	
	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,                  // VerticesID
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,                  // NormalID
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,					// stride
		(void*)VERTBUFFERSIZE
	);

	// 3rd attribute buffer : textures
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(
		2,                  // TextureID
		2,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)(VERTBUFFERSIZE + NORMBUFFERSIZE)
	);

	// 4th attribute buffer : color
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(
		3,                  // ColorID
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)(VERTBUFFERSIZE + NORMBUFFERSIZE + TEXTBUFFERSIZE)
	);

	glBindBuffer(GL_ARRAY_BUFFER, 0); /// Unbinds the buffer by setting it to zero   
	glBindVertexArray(0); // Disable the VBO  
	glEnableVertexAttribArray(0); // Disable the VAO

	brightLoc = glGetUniformLocation(shaderID, "brightness");
	opaqueLoc = glGetUniformLocation(shaderID, "opaqueness");
	modelLoc = glGetUniformLocation(shaderID, "model");
	viewLoc = glGetUniformLocation(shaderID, "view");
	projLoc = glGetUniformLocation(shaderID, "proj");
	textLoc = glGetUniformLocation(shaderID, "inputTexture");
	viewPosLoc = glGetUniformLocation(shaderID, "viewPosition");
	lightPosLoc = glGetUniformLocation(shaderID, "light.pos");
	lightAmbLoc = glGetUniformLocation(shaderID, "light.ambient");
	lightDiffLoc = glGetUniformLocation(shaderID, "light.diffuse");
	lightColLoc = glGetUniformLocation(shaderID, "light.color");
	//Material shader disabled to be reinmplemented at a later date
	useMat = false;

	matDiffLoc = glGetUniformLocation(shaderID, "mtl.diffMap");
	matNsLoc = glGetUniformLocation(shaderID, "mtl.Ns");
	matNiLoc = glGetUniformLocation(shaderID, "mtl.Ni");
	matDLoc = glGetUniformLocation(shaderID, "mtl.d");
	matTfLoc = glGetUniformLocation(shaderID, "mtl.Tf");
	matTrLoc = glGetUniformLocation(shaderID, "mtl.Tr");
	matKaLoc = glGetUniformLocation(shaderID, "mtl.Ka");
	matKdLoc = glGetUniformLocation(shaderID, "mtl.Kd");
	matKsLoc = glGetUniformLocation(shaderID, "mtl.Ks");
	matKeLoc = glGetUniformLocation(shaderID, "mtl.Ke");

#undef VERTBUFFERSIZE
#undef NORMBUFFERSIZE
#undef TEXTBUFFERSIZE
#undef COLOBUFFERSIZE

}

void Mesh::render(glm::mat4 transformation_, meshProperties properties_) {

	if (!setup)
		setupMesh();

	glUniform1i(textLoc, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	/*
	glUniform3f(viewPosLoc, Camera::GetInstance()->getPosition().x, Camera::GetInstance()->getPosition().y, Camera::GetInstance()->getPosition().z);
	glUniform3f(lightPosLoc, Camera::GetInstance()->getLightSources()[0]->GetPosition().x, Camera::GetInstance()->getLightSources()[0]->GetPosition().y, Camera::GetInstance()->getLightSources()[0]->GetPosition().z);
	glUniform1f(lightAmbLoc, Camera::GetInstance()->getLightSources()[0]->GetAmbient());
	glUniform1f(lightDiffLoc, Camera::GetInstance()->getLightSources()[0]->GetDiffuse());
	glUniform3f(lightColLoc, Camera::GetInstance()->getLightSources()[0]->GetLightColor().x, Camera::GetInstance()->getLightSources()[0]->GetLightColor().y, Camera::GetInstance()->getLightSources()[0]->GetLightColor().z);
	*/
	if (useMat) {

		glUniform1i(matDiffLoc, Mat.diffMap);
		glUniform1f(matNsLoc, Mat.Ns);
		glUniform1f(matNiLoc, Mat.Ni);
		glUniform1f(matDLoc, Mat.d);
		glUniform1f(matTrLoc, Mat.Tr);

		glUniform3f(matTfLoc, Mat.Tf.x, Mat.Tf.y, Mat.Tf.z);
		glUniform3f(matKaLoc, Mat.Ka.x, Mat.Ka.y, Mat.Ka.z);
		glUniform3f(matKdLoc, Mat.Kd.x, Mat.Kd.y, Mat.Kd.z);
		glUniform3f(matKsLoc, Mat.Ks.x, Mat.Ks.y, Mat.Ks.z);
		glUniform3f(matKeLoc, Mat.Ke.x, Mat.Ke.y, Mat.Ke.z);

	}

	glUseProgram(shaderID);
	if (shaderID == 0)
		return;
	glUniform1f(brightLoc, properties_.brightness);
	glUniform1f(opaqueLoc, properties_.opaqueness);
	glUniform3f(colorLoc, properties_.color.x, properties_.color.y, properties_.color.z);
	glUniform3f(particleLightColLoc, properties_.lightColor.x, properties_.lightColor.y, properties_.lightColor.z);
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transformation_));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera->getView()));
	if(twoD)
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera->getOrthographic()));
	else
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera->getPerspective()));
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size()); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);

}
