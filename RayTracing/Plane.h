#pragma once
#include <glm/glm.hpp>
#include "Raycast.h"
#include "Shape.h"

class Plane : public Shape
{
	glm::vec3 origin;
	glm::vec3 norm;
	glm::vec3 color;
	float matIntensity;
	
public:
	Plane(glm::vec3 _origin, glm::vec3 _normal, glm::vec3 _color, float _matIntensity);
	bool OnIntersection(Raycast & ray, float & t);
	glm::vec3 normal(const glm::vec3 & pi) const;
	glm::vec3 getColor();
	float getIntensity();
	~Plane();
};

