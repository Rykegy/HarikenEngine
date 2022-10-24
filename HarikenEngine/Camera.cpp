#include "stdafx.h"
#include "Camera.h"
#include "WindowSys.h"

using namespace HARIKEN;

std::unique_ptr<Camera> Camera::cameraInstance = nullptr;

Camera::Camera() : position(glm::vec3(0.0f, 0.0f, 10.0f)), perspective(glm::mat4()), orthographic(glm::mat4()), FOV(0.0f), yaw(0.0f), pitch(0.0f), forwardVector(glm::vec3()), upVector(glm::vec3()), rightVector(glm::vec3()), worldUp(glm::vec3()), lights(std::vector<LightSource*>())
{

	FOV = 45.0f;
	forwardVector = glm::vec3(0.0f, 0.0f, -1.0f);
	upVector = glm::vec3(0.0f, 1.0f, 0.0f);
	worldUp = upVector;
	nearPlane = 0.01f;
	farPlane = 100.0f;
	yaw = -90.0f;

	perspective = glm::perspective(FOV, WindowSys::GetInstance()->getWinSize().x / WindowSys::GetInstance()->getWinSize().y, nearPlane, farPlane);
	orthographic = glm::ortho(-WindowSys::GetInstance()->getWinSize().x / 2, WindowSys::GetInstance()->getWinSize().x / 2, WindowSys::GetInstance()->getWinSize().y / 2, -WindowSys::GetInstance()->getWinSize().y / 2, nearPlane, farPlane);
	alListenerfv(AL_POSITION, ALVec3(position).values);

}


Camera::~Camera()
{

	for (auto l : lights) {

		delete l;
		l = nullptr;

	}
	lights.clear();
	lights.shrink_to_fit();

}

void Camera::updateCameraVectors()
{
	forwardVector.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	forwardVector.y = sin(glm::radians(pitch));
	forwardVector.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	forwardVector = glm::normalize(forwardVector);

	rightVector = glm::normalize(glm::cross(forwardVector, worldUp));
	upVector = glm::normalize(glm::cross(rightVector, forwardVector));
}

Camera* Camera::GetInstance() {

	if (cameraInstance.get() == nullptr)
		cameraInstance.reset(new Camera);

	return cameraInstance.get();

}

void Camera::setPosition(glm::vec3 position_)
{
	position = position_ * *WindowSys::GetInstance()->positionScale;
	updateCameraVectors();
}

void Camera::setRotation(GLfloat yaw_, GLfloat pitch_)
{
	yaw = yaw_;
	pitch = pitch_;
	updateCameraVectors();
}

glm::mat4 Camera::getView() const
{
	return glm::lookAt(position, position + forwardVector, upVector);
}

glm::mat4 Camera::getPerspective() const
{
	return perspective;
}

glm::mat4 Camera::getOrthographic() const
{
	return orthographic;
}

glm::vec3 HARIKEN::Camera::getPosition() const
{
	return position;
}

void HARIKEN::Camera::addLightSource(LightSource * light_)
{

	lights.push_back(light_);

}

std::vector<LightSource*> HARIKEN::Camera::getLightSources() const
{
	return lights;
}

float HARIKEN::Camera::getNearPlane()
{
	return nearPlane;
}

float HARIKEN::Camera::getFarPlane()
{
	return farPlane;
}
