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

	virtual glm::vec3 getPosition();
	virtual glm::vec3 getColor();
	virtual glm::vec3 normal(const glm::vec3 & pi ) const = 0;
	virtual float getIntensity();
	
	virtual bool OnIntersection(Raycast & ray, float & t) = 0;

	~Shape();
};

