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

bool Shape::OnIntersection(Raycast & ray, float & t)
{
	return false;
}


Shape::~Shape()
{
}
