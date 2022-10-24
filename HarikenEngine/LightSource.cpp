#include "stdafx.h"
#include "LightSource.h"


LightSource::LightSource(glm::vec3 position_, float ambient_, float diffuse_, glm::vec3 lightColor_)
{
	setPosition(position_);
	setAmbient(ambient_);
	setDiffuse(diffuse_);
	setLightColor(lightColor_);
}

LightSource::~LightSource()
{
}

glm::vec3 LightSource::GetPosition() const
{
	return position;
}

float LightSource::GetAmbient() const
{
	return ambient;
}

float LightSource::GetDiffuse() const
{
	return diffuse;
}

glm::vec3 LightSource::GetLightColor() const
{
	return lightColor;
}

void LightSource::setPosition(glm::vec3 position_)
{

	position = position_;

}

void LightSource::setAmbient(float ambient_)
{

	ambient = ambient_;

}

void LightSource::setDiffuse(float diffuse_)
{

	diffuse = diffuse_;

}

void LightSource::setLightColor(glm::vec3 lightColor_)
{

	lightColor = lightColor_;

}
