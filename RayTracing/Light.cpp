#include "pch.h"
#include "Light.h"
#include <glm/glm.hpp>

Light::Light(glm::vec3 _position, glm::vec3 _ambientIntesity, glm::vec3 _diffuseIntensity, glm::vec3 _specularIntensity)
{
	position = _position;
	ambientIntensity = _ambientIntesity;
	diffuseIntensity = _diffuseIntensity;
	specularIntensity = _specularIntensity;
}

glm::vec3 Light::getAmbientIntensity()
{
	return ambientIntensity;
}

glm::vec3 Light::getDiffuseIntensity() {
	return diffuseIntensity;
}

glm::vec3 Light::getSpecularIntensity() {
	return specularIntensity;
}

glm::vec3 Light::getPosition() {
	return position;
}

Light::~Light()
{
}
