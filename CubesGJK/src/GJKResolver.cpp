#include "GJKResolver.h"

GJKResolver::GJKResolver() :
	separationVector(glm::vec3(0.0f))
{}

const glm::vec3 GJKResolver::getSeparationVector() const
{
	return this->separationVector;
}

GLboolean GJKResolver::areCubesNotColliding(const Cube& cube1, const Cube& cube2)
{
	return ~this->areCubesColliding(cube1, cube2);
}

GLboolean GJKResolver::areCubesColliding(const Cube& cube1, const Cube& cube2)
{
	this->separationVector = glm::vec3(0.0f);
	glm::vec3 supportPoint = this->findSupportPointOnDirection(cube1, cube2, glm::vec3(1.0f, 0.0f, 0.0f));
	Simplex simplex;
	simplex.pushFront(supportPoint);

	glm::vec3 direction = -supportPoint;
	while (true)
	{
		supportPoint = this->findSupportPointOnDirection(cube1, cube2, direction);

		if (glm::dot(supportPoint, direction) <= 0)
		{
			return false;
		}

		simplex.pushFront(supportPoint);
		
		if (simplex.isOriginInSimplex(direction))
		{
			this->separationVector = simplex
				.sort()
				.getSimplexPoints()[0];
			return true;
		}
	}
}

glm::vec3 GJKResolver::findSupportPointOnDirection(const Cube& cube1, const Cube& cube2, const glm::vec3& direction)
{
	return this->findFurthestPointOnDirection(cube1, direction) 
		- this->findFurthestPointOnDirection(cube2, -direction);
}

const glm::vec3 GJKResolver::findFurthestPointOnDirection(const Cube& cube, const glm::vec3& direction) const
{
	std::vector<glm::vec3> vertices;
	for (unsigned int i = 0; i < CUBE_VERTICES_NUMBER; i++)
	{
		glm::vec4 vertex = glm::vec4(cube.getVertices()[i], 1.0f) * cube.getModelMatrixTransposed();
		vertices.push_back(vertex);
	}
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
