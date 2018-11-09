#include "pch.h"
#include "Plane.h"


Plane::Plane(glm::vec3 _origin, glm::vec3 _normal, glm::vec3 _color, float _matIntensity)
{
	origin = _origin;
	norm = normalize(_normal);
	color = _color;
	matIntensity = _matIntensity;
}

bool Plane::OnIntersection(Raycast & ray, float & t)
{
	glm::vec3 rayDir = ray.getDirection();
	glm::vec3 rayOrigin = ray.getOrigin();
	float dom = glm::dot(rayDir, norm);
	if (dom == 0)
		return false;

	t = glm::dot((origin - rayOrigin), norm) / dom;
	if (t <= 0)
		return false;

	return true;
}

glm::vec3 Plane::normal(const glm::vec3 & pi) const
{
	return norm;
}

glm::vec3 Plane::getColor()
{
	return color;
}

float Plane::getIntensity()
{
	return matIntensity;
}

Plane::~Plane()
{
}
