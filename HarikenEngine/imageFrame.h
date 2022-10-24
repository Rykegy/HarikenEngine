/**************************************************
Special model class used for displaying 2D images on OpenGL.
**************************************************/

#pragma once
#include "Model.h"

namespace HARIKEN {

	class imageFrame : public Model
	{
	public:
		imageFrame();
		imageFrame(float width, float height, GLuint textureID_);
		imageFrame(float width, float height, GLuint textureID_, bool isText);
		virtual ~imageFrame();

		glm::vec3 getSize();

		void render();

	private:
		glm::vec3 size;
		bool isText;

	};

}