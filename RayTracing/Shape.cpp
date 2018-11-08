#include "pch.h"
#include "Shape.h"


Shape::Shape()
{

}

glm::vec3 Shape::getPosition()
{
	return myCenter;
}

glm::vec3 Shape::getColor()
{
	return myColor;
}

glm::vec3 Shape::normal(const glm::vec3 & pi) const
{
	return glm::vec3(0,0,0);
}

float Shape::getIntensity()
{
	return matIntensity;
}

bool Shape::OnIntersection(Raycast & ray, float & t)
{
	return false;
}


Shape::~Shape()
{
}
