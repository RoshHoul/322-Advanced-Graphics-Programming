#pragma once
#include <glm/glm.hpp>
#include "Raycast.h"

class Shape
{
protected:
	glm::vec3 myCenter;
	glm::vec3 myColor;
	float matIntensity;

public:
	Shape();
	
	glm::vec3 getPosition();
	glm::vec3 getColor();
	glm::vec3 normal(const glm::vec3 & pi ) const;
	float getIntensity();
	
	bool OnIntersection(Raycast & ray, float & t);

	~Shape();
};

