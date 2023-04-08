#include "GJKCollisionChecker.h"

glm::vec3 GJKCollisionChecker::findFurthestPointOnDirection(Cube& cube, glm::vec3 direction)
{
	std::vector<glm::vec3> vertices = cube.getTranslatedVertices();
	
	glm::vec3 maxPoint;
	GLfloat maxDistance = -INFINITY;

	for (glm::vec3 vertex : vertices)
	{
		GLfloat distance = glm::dot(vertex, direction);
		if (distance > maxDistance)
		{
			maxDistance = distance;
			maxPoint = vertex;
		}
	}
	
	return maxPoint;
}

glm::vec3 GJKCollisionChecker::findSupportPoint(Cube& cube1, Cube& cube2, glm::vec3 direction)
{
	return this->findFurthestPointOnDirection(cube1, direction) - this->findFurthestPointOnDirection(cube2, -direction);
}

void GJKCollisionChecker::renderSimplex(Shader& shader)
{
	this->points.render(shader);
}
