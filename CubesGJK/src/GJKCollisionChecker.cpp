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
	std::vector<glm::vec3> verticesOfBothCubes;
	for (int i = 0; i < cube1.getTranslatedVertices().size(); i++)
	{
		for (int j = 0; j < cube2.getTranslatedVertices().size(); j++)
		{
			verticesOfBothCubes.push_back(cube1.getTranslatedVertices()[i] - cube2.getTranslatedVertices()[j]);
		}
	}
	for (int i = 1; i < verticesOfBothCubes.size(); i++)
	{
		Line::drawLine(shader, verticesOfBothCubes[i], Colors::Green, verticesOfBothCubes[i - 1], Colors::Green);
	}
}
