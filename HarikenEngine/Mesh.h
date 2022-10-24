/***************************************************
Used to store mesh data such as vertices and color in a model.
***************************************************/

#pragma once
#include <vector>
#include <glm.hpp>
#include <glew.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <gtc/type_ptr.hpp>
#include "Camera.h"
#include "ShaderHandler.h"

namespace HARIKEN {

	struct vertex
	{

		vertex() : position(glm::vec3(0.0f, 0.0f, 0.0f)), normal(glm::vec3(0.0f, 0.0f, 0.0f)), texture(glm::vec3(0.0f, 0.0f, 0.0f)), color(glm::vec3(1.0f, 1.0f, 1.0f)) {}

		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texture;
		glm::vec3 color;

	};

	struct mtl {

		mtl() : diffMap(0), Ns(0.0f), d(0.0f), Tr(0.0f), Tf(glm::vec3(1.0f)), Ka(glm::vec3(1.0f)), Kd(glm::vec3(1.0f)), Ks(glm::vec3(1.0f)), Ke(glm::vec3(1.0f)) {}

		GLuint diffMap;

		float Ns;
		float Ni;
		float d;
		float Tr;
		glm::vec3 Tf;
		glm::vec3 Ka;
		glm::vec3 Kd;
		glm::vec3 Ks;
		glm::vec3 Ke;

	};

	struct meshProperties {

		GLfloat brightness = 1.0f;
		GLfloat opaqueness = 1.0f;
		glm::vec3 color = glm::vec3();
		glm::vec3 lightColor = glm::vec3();

		meshProperties() {};

	};

	class Mesh
	{
	public:
		Mesh(std::vector<vertex> vertices_);
		Mesh(std::vector<vertex> vertices_, GLuint textureID_, mtl mat);
		Mesh(std::vector<vertex> vertices_, GLuint textureID_, GLuint shaderID_);
		virtual ~Mesh();

		GLuint getTextureID();

		void render(glm::mat4 transform_, meshProperties properties);

		GLenum drawmode;
		std::vector<vertex> vertices;
		mtl Mat;

	protected:

		GLuint vbo;
		GLuint vao;
		GLuint ubo;

		std::vector<GLfloat> g_vertex_buffer_data;
		std::vector<GLfloat> g_normal_buffer_data;
		std::vector<GLfloat> g_texture_buffer_data;
		std::vector<GLfloat> g_color_buffer_data;

		GLuint shaderID;
		GLuint textureID;
		GLuint brightLoc;
		GLuint opaqueLoc;
		GLuint colorLoc;
		GLuint particleLightColLoc;
		GLuint modelLoc;
		GLuint viewLoc;
		GLuint projLoc;
		GLuint textLoc;
		GLuint viewPosLoc;
		GLuint lightPosLoc;
		GLuint lightAmbLoc;
		GLuint lightDiffLoc;
		GLuint lightColLoc;

		GLuint matDiffLoc;
		GLuint matNsLoc;
		GLuint matNiLoc;
		GLuint matDLoc;
		GLuint matTfLoc;
		GLuint matTrLoc;
		GLuint matKaLoc;
		GLuint matKdLoc;
		GLuint matKsLoc;
		GLuint matKeLoc;

		bool useMat = false;

		void setupMesh();
		void setupMeshMat();

		Camera* camera;
		bool twoD;
		bool deleteTexture = true;

		bool setup = false;

	};

}