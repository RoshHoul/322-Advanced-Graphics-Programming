#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "Raycast.h"
#include "Shape.h"

class Sphere : public Shape
{
	float myRadius;
	float rad2;

public:
	Sphere(glm::vec3 center, float radius, glm::vec3 color, float _matIntensity);
	
	float getRadius();
	
	glm::vec3 getPosition();
	glm::vec3 getColor();
	glm::vec3 normal(const glm::vec3 & pi) const;

	bool solveQuadrics(float const & a, float const & b, float const & c, float & x0, float x1);
	bool OnIntersection(Raycast & ray, float & t);
	~Sphere();
};

