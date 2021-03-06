#pragma once
#include <glm/glm.hpp>
#include "Shape.h"

class Box : public Shape
{
	glm::vec3 bounds[2];
public:
	Box(const glm::vec3 &min, const glm::vec3 &max, glm::vec3 color);
	glm::vec3 getColor();
	glm::vec3 normal(const glm::vec3 & pi) const;

	bool OnIntersection(Raycast & ray, float & t);
	~Box();
};

