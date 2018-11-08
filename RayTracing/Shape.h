#pragma once
#include <glm/glm.hpp>
#include "Raycast.h"

class Shape
{
protected:
	glm::vec3 myCenter;
	glm::vec3 myColor;

public:
	Shape();
	
	glm::vec3 getPosition();
	glm::vec3 getColor();
	bool OnIntersection(Raycast & ray, float & t);

	~Shape();
};

