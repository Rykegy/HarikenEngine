/*********************************
Special mesh used for text (deprecated).
*********************************/

#pragma once
#include "Mesh.h"

namespace HARIKEN {

	class textMesh : public Mesh
	{
	public:

		textMesh(std::vector<vertex> vertices_, GLuint textureID_, GLuint shaderID_);
		~textMesh();

		void render(glm::mat4 transform_, meshProperties properties);

	private:

	};

}