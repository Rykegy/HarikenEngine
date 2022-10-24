/********************************
Special model used to display particles.
********************************/

#pragma once
#include <glew.h>
#include "Model.h"

namespace HARIKEN {
	class particleFrame : public Model
	{
	public:
		particleFrame();
		~particleFrame();

		particleFrame(float width, float height, GLuint textureID_);
		particleFrame(float width, float height, GLuint textureID_, glm::vec3 color_);
	};

}