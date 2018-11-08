#include "pch.h"
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include "Raycast.h"
#include "Sphere.h"


Sphere::Sphere(glm::vec3 center, float radius, glm::vec3 color, float _matIntensity) 
{
	myRadius = radius;
	myCenter = center;
	myColor = color;
	matIntensity = _matIntensity;
	rad2 = myRadius * myRadius;
}

glm::vec3 Sphere::getPosition() {
	return myCenter;
}

float Sphere::getRadius() {
	return myRadius;
}

glm::vec3 Sphere::getColor() {
	return myColor;
}

glm::vec3 Sphere::normal(const glm::vec3& pi) const { 
	return (pi - myCenter) / (float)myRadius; 
}

bool Sphere::solveQuadrics(float const &a, float const &b, float const &c, float &x0, float x1) {
	float discr = b * b - 4 * a*c;

	if (discr < 0)
		return false;

	else if (discr == 0)
		x0 = x1 = -0.5 * b / a;

	else {
		float q = b > 0 ?
			-0.5 * (b + sqrt(discr)) :
			-0.5 * (b - sqrt(discr));

		x0 = q / a;
		x1 = c / q;
	}

	if (x0 > x1) std::swap(x0, x1);

	return true;
}


bool Sphere::OnIntersection(Raycast &ray, float& t) {

	float t0 = 50000;
	float t1 = 50000;
	glm::vec3 origin = ray.getOrigin();
	glm::vec3 dir = ray.getDirection();


	glm::vec3 l = origin - myCenter;
	float a = glm::dot(dir, dir);
	float b = 2 * glm::dot(l, dir);
	float c = glm::dot(l, l) - rad2;
	if (!solveQuadrics(a, b, c, t0, t1))
		return false;
	if (t0 > t1)
		std::swap(t0, t1);

	if (t0 < 0) {
		t0 = t1;
		if (t0 < 0) {
			return false;
		}
	}

	t = t0;


	return true;
}








Sphere::~Sphere()
{
}
