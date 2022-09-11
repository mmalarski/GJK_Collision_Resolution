#include "GJKResolver.h"

glm::vec3 GJKResolver::findSupportPointOnDirection(const Cube& cube1, const Cube& cube2, const glm::vec3& direction)
{
	return this->findFurthestPointOnDirection(cube1, direction) 
		- this->findFurthestPointOnDirection(cube2, -direction);
}

const glm::vec3 GJKResolver::findFurthestPointOnDirection(const Cube& cube, const glm::vec3& direction) const
{
	const glm::vec3* vertices = cube.getVertices();
	glm::vec3 furthestPointOnDirection = glm::vec3(0.0f);
	GLfloat maxDistance = -FLT_MAX;
	for (unsigned int i = 0; i < CUBE_VERTICES_NUMBER; i++)
	{
		GLfloat distance = glm::dot(vertices[i], direction);
		if (distance > maxDistance)
		{
			maxDistance = distance;
			furthestPointOnDirection = vertices[i];
		}
	}
	return furthestPointOnDirection;
}

GJKResolver::Simplex::Simplex()
{
	this->points = { 
		glm::vec3(0.0f),
		glm::vec3(0.0f),
		glm::vec3(0.0f),
		glm::vec3(0.0f) };
	this->size = 0;
}

GJKResolver::Simplex& GJKResolver::Simplex::operator=(std::initializer_list<glm::vec3> list)
{
	for (auto point = list.begin(); point != list.end(); point++)
	{
		this->points[std::distance(list.begin(), point)] = *point;
	}
	this->size = list.size();
	return *this;
}

glm::vec3 GJKResolver::Simplex::operator[](GLuint i)
{
	return this->points[i];
};

void GJKResolver::Simplex::pushFront(const glm::vec3 point)
{
	this->points = { point, this->points[0], this->points[1], this->points[2] };
	this->size = glm::min(this->size + 1, 4u);
}

GLuint GJKResolver::Simplex::getSize() const
{
	return this->size;
}

auto GJKResolver::Simplex::begin() const
{
	return this->points.begin();
}

auto GJKResolver::Simplex::end() const
{
	return this->points.end();
}
