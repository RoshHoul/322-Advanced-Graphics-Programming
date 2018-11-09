#pragma once
#include <glm/glm.hpp>
#include "Shape.h"

class Triangle : public Shape
{
	glm::vec3 v0, v1, v2;
	float t, u, v;

public:
	Triangle(glm::vec3 _v0, glm::vec3 _v1, glm::vec3 _v2);
	glm::vec3 normal(const glm::vec3 & pi) const;
	bool OnIntersection(Raycast & ray, float & t);
	~Triangle();
};

