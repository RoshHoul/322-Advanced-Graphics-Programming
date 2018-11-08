#include "pch.h"
#include "Raycast.h"


Raycast::Raycast(glm::vec3 origin, glm::vec3 dir) 
{
	myOrigin = origin;
	direction = dir;
}


glm::vec3 Raycast::getOrigin() {
	return myOrigin;
}

void Raycast::setDirection(glm::vec3 dir) {
	direction = dir;
	glm::normalize(direction);
}

glm::vec3 Raycast::getDirection() {
	return direction;
}


Raycast::~Raycast()
{
}
