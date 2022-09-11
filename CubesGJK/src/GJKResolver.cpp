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
