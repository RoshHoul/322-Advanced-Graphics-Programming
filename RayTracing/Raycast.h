#pragma once

#include "glm/glm.hpp"

class Raycast
{
	glm::vec3 myOrigin;
	glm::vec3 direction;

public:
	Raycast(glm::vec3 origin, glm::vec3 dir);
	glm::vec3 getOrigin();
	void setDirection(glm::vec3 dir);
	glm::vec3 getDirection();
	~Raycast();
};

