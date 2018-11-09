#pragma once
#include <vector>;
#include <glm/glm.hpp>
#include "Triangle.h"
class Object
{
protected:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<Triangle> triangles;
	glm::vec3 color;
	glm::vec3 position;

public:
	Object(const char *filePath, glm::vec3 _position, glm::vec3 _color);
	bool loadOBJ(const char * path,
		std::vector<glm::vec3> & out_vertices,
		std::vector<glm::vec3> & out_normals);
	std::vector<Triangle> getFaces();
	glm::vec3 getColor();
	bool onInterestion(Raycast & ray, float & t);
	~Object();
};

