#include "pch.h"
#include "Triangle.h"



Triangle::Triangle(glm::vec3 _v0, glm::vec3 _v1, glm::vec3 _v2)
{
	v0 = _v0;
	v1 = _v1;
	v2 = _v2;
}

glm::vec3 Triangle::normal(const glm::vec3 & pi) const
{
	return glm::vec3();
}

bool Triangle::OnIntersection(Raycast & ray, float & t)
{
	glm::vec3 origin = ray.getOrigin();
	glm::vec3 dir = ray.getDirection();

	glm::vec3 v0v1 = v1 - v0;
	glm::vec3 v0v2 = v2 - v0;
	glm::vec3 N = glm::cross(v0v1, v0v2);
	
	float area2 = N.length();

	float NdotRayDirection = glm::dot(N, dir);

	if (fabs(NdotRayDirection) < 0.1f)
		return false;

	float d = glm::dot(N, v0);

	t = glm::dot(N, v0);

	if (t < 0)
		return false;

	glm::vec3 ip = origin + t * dir;

	glm::vec3 C;

	glm::vec3 edge0 = v1 - v0;
	glm::vec3 vp0 = ip - v0;
	C = glm::cross(edge0, vp0);

	if (glm::dot(N, C) < 0)
		return false;

	glm::vec3 edge1 = v2 - v1;
	glm::vec3 vp1 = ip - v1;
	C = glm::cross(edge1, vp1);

	if (glm::dot(N, C) < 0)
		return false;

	glm::vec3 edge2 = v0 - v2;
	glm::vec3 vp2 = ip - v2;
	C = glm::cross(edge2, vp2);

	if (glm::dot(N, C) < 0)
		return false;

	return true;
}

Triangle::~Triangle()
{
}
