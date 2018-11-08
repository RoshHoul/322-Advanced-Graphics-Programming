#pragma once
#include <glm/glm.hpp>

class Light
{
	glm::vec3 position;
	glm::vec3 ambientIntensity;
	glm::vec3 diffuseIntensity;
	glm::vec3 specularIntensity;


public:
	Light(glm::vec3 _position, glm::vec3 ambientIntensity, glm::vec3 _diffuseIntensity, glm::vec3 specularIntensity);
	glm::vec3 getAmbientIntensity();
	glm::vec3 getDiffuseIntensity();
	glm::vec3 getSpecularIntensity();
	glm::vec3 getPosition();
	~Light();
};

