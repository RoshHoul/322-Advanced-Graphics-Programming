#include "pch.h"
#include "Box.h"

Box::Box(const glm::vec3 &min, const glm::vec3 &max, glm::vec3 color)
{
	bounds[0] = min;
	bounds[1] = max;
	myColor = color;

}

glm::vec3 Box::getColor()
{
	return myColor;
}

bool Box::OnIntersection(Raycast &ray, float &t) {

	float tmin = (bounds[0].x - ray.getOrigin().x) / ray.getDirection().x;
	float tmax = (bounds[1].x - ray.getOrigin().x) / ray.getDirection().x;

	if (tmin > tmax)
		std::swap(tmin, tmax);

	float tYmin = (bounds[0].y - ray.getOrigin().y) / ray.getDirection().y;
	float tYmax = (bounds[1].y - ray.getOrigin().y) / ray.getDirection().y;

	if ((tmin > tYmax) || (tYmin > tmax))
		return false;

	if (tYmin > tmin)
		tmin = tYmin;
	if (tYmax < tmax)
		tmax = tYmax;

	float tZmin = (bounds[0].z - ray.getOrigin().z) / ray.getDirection().z;
	float tZmax = (bounds[1].z - ray.getOrigin().z) / ray.getDirection().z;

	if (tZmin > tZmax)
		std::swap(tZmin, tZmax);

	if ((tmin > tZmax) || (tZmin > tmax))
		return false;

	if (tZmin > tmin)
		tmin = tZmin;

	if (tZmax < tmax)
		tmax = tZmax;

	return true;
}

Box::~Box()
{
}
