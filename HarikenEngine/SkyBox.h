#pragma once
#include <glm.hpp>
#include <glew.h>
#include "ShaderHandler.h"
#include "Mesh.h"

namespace HARIKEN {

	class SkyBox
	{
	public:
		SkyBox();
		~SkyBox();

		virtual bool init();
		virtual void onCreate() = 0;
		virtual void update() = 0;
		virtual const void render() = 0;
		virtual void Destroy();

	protected:

		GLuint vbo;
		GLuint vao;
		GLint verticiesID;
		GLint normalsID;
		GLint uvCoordsID;
		GLuint shaderID;

		GLint projectionMatrixID;
		GLint modelViewMatrixID;
		GLint normalMatrixID;
		GLint lightPosID;
		glm::vec3 lightPos;

		std::vector<Mesh*> meshes;

	};

}