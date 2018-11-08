#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "Raycast.h"
#include "Shape.h"

class Sphere : Shape
{
	glm::vec3 myCenter, myColor;
	std::vector<glm::vec3> myVertices;
	float myRadius;
	float rad2;

public:
	Sphere(glm::vec3 center, float radius, glm::vec3 color);
	
	float getRadius();
	
	glm::vec3 getPosition();
	glm::vec3 getColor();
	glm::vec3 normal(const glm::vec3 & pi) const;

	void makeSphere();

	bool solveQuadrics(float const & a, float const & b, float const & c, float & x0, float x1);
	bool OnIntersection(Raycast & ray, float & t);
	~Sphere();
};

