/**********************************************************
Used for 3D scenes for shaders to determing the lighting for 3D models.
**********************************************************/

#pragma once
#include <glm.hpp>
class LightSource
{
public:
	LightSource(glm::vec3 position_, float ambient_, float specular_, glm::vec3 lightColor_);
	~LightSource();

	glm::vec3 GetPosition() const;
	float GetAmbient() const;
	float GetDiffuse() const;
	glm::vec3 GetLightColor() const;

	void setPosition(glm::vec3 position_);
	void setAmbient(float ambient_);
	void setDiffuse(float specular_);
	void setLightColor(glm::vec3 lightColor_);

private:
	glm::vec3 position;
	float ambient;
	float diffuse;
	glm::vec3 lightColor;

};

