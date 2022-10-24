#pragma once
#include "Model.h"

namespace HARIKEN {

	class cubeModel : public Model
	{
	public:
		cubeModel(GLuint textureID_, GLuint shaderID_);
		~cubeModel();
	};

}