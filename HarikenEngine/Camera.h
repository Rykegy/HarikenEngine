/****************************************************************************************
Class used to determine where objects are in relation to the origin and in what way they are to be rendered.
****************************************************************************************/

#pragma once
#include <glm.hpp>
#include <glew.h>
#include <memory>
#include <gtc/matrix_transform.hpp>
#include <vector>
#include "LightSource.h"

namespace HARIKEN {

	class Camera
	{
	public:
		Camera(const Camera&) = delete;
		Camera(Camera&&) = delete;
		Camera& operator = (const Camera&) = delete;
		Camera& operator = (Camera&&) = delete;

		static Camera* GetInstance();

		void setPosition(glm::vec3 position_);
		void setRotation(GLfloat yaw_, GLfloat pitch);
		glm::mat4 getView() const;
		glm::mat4 getPerspective() const;
		glm::mat4 getOrthographic() const;
		glm::vec3 getPosition() const;

		void addLightSource(LightSource* light_);
		std::vector<LightSource*> getLightSources() const;

		float getNearPlane();
		float getFarPlane();

	private:
		Camera();
		~Camera();
		static std::unique_ptr<Camera> cameraInstance;
		friend std::default_delete<Camera>;

		void updateCameraVectors();

		glm::vec3 position;
		glm::mat4 perspective;
		glm::mat4 orthographic;

		GLfloat FOV;
		GLfloat yaw;
		GLfloat pitch;
		GLfloat nearPlane;
		GLfloat farPlane;

		glm::vec3 forwardVector;
		glm::vec3 upVector;
		glm::vec3 rightVector;
		glm::vec3 worldUp;

		std::vector<LightSource*> lights;

	};

}