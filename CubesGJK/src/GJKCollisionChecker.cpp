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

GLboolean GJKCollisionChecker::checkCollision(Cube& cube1, Cube& cube2)
{
	glm::vec3 support = findSupportPoint(cube1, cube2, cube1.getPosition() - cube2.getPosition());
	points.pushFront(support);
	glm::vec3 direction = -support;
	while (true)
	{
		support = findSupportPoint(cube1, cube2, direction);
		if (glm::dot(support, direction) < 0)
		{
			return GL_FALSE;
		}
		points.pushFront(support);
		//if (this->doSimplex(direction))
		//{
		//	return GL_TRUE;
		//}
	}
	
	return GLboolean();
}

void GJKCollisionChecker::renderMinkowskiDifference(Shader& shader, Cube& cube1, Cube& cube2)
{
	for (const glm::vec3& vertex : cube1.getTranslatedVertices())
	{
		for (const glm::vec3& vertex2 : cube2.getTranslatedVertices())
		{
			if (vertex == vertex2) continue;
			Line::drawLine(
				shader,
				vertex2 - vertex,
				Colors::Green,
				vertex - vertex2,
				Colors::Green
			);
		}
	}
}

void GJKCollisionChecker::renderSimplex(Shader& shader)
{
	this->points.render(shader);
}
