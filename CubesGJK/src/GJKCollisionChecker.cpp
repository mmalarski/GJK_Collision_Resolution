#include "GJKCollisionChecker.h"

glm::vec3 GJKCollisionChecker::findFurthestPointOnDirection(Cube& cube, glm::vec3 direction)
{
	std::vector<glm::vec3> vertices = cube.getTranslatedVertices();
	
	glm::vec3 maxPoint;
	GLfloat maxDistance = -INFINITY;

	for (glm::vec3 vertex : vertices)
	{
		GLfloat distance = glm::dot(direction, vertex);
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
	this->points.pushFront(support);
	glm::vec3 direction = -support;
	while (true)
	{
		support = findSupportPoint(cube1, cube2, direction);
		if (glm::dot(support, direction) <= 0)
		{
			return GL_FALSE;
		}
		points.pushFront(support);
		if (this->nextSimplex(this->points, direction))
		{
			return GL_TRUE;
		}
	}

	return GL_FALSE;
}

GLboolean GJKCollisionChecker::nextSimplex(Simplex& simplex, glm::vec3& direction)
{
	switch (this->points.size())
	{
	case 2: return Line(this->points, direction);
	case 3: return Triangle(this->points, direction);
	case 4: return Tetrahedron(this->points, direction);
	}
	
	return GL_FALSE;
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

GLboolean GJKCollisionChecker::Line(Simplex& simplex, glm::vec3& direction)
{
	glm::vec3 a = points[0];
	glm::vec3 b = points[1];

	glm::vec3 ab = b - a;
	glm::vec3 ao = -a;

	if (SameDirection(ab, ao)) {
		direction = glm::cross(glm::cross(ab ,ao), ab); //??? kolejnosc
	}

	else {
		points = { a };
		direction = ao;
	}

	return GL_FALSE;
}

GLboolean GJKCollisionChecker::Triangle(Simplex& simplex, glm::vec3& direction)
{
	glm::vec3 a = points[0];
	glm::vec3 b = points[1];
	glm::vec3 c = points[2];

	glm::vec3 ab = b - a;
	glm::vec3 ac = c - a;
	glm::vec3 ao = -a;

	glm::vec3 abc = glm::cross(ac, ab);
	glm::vec3 abcCrossAc = glm::cross(ac, abc);
	glm::vec3 abCrossAbc = glm::cross(abc, ab);

	if (SameDirection(abcCrossAc, ao)) {
		if (SameDirection(ac, ao)) {
			points = { a, c };
			direction = glm::cross(glm::cross(ac, ao), ac); //??? kolejnosc
		}

		else {
			return Line(points = { a, b }, direction);
		}
	}

	else {
		if (SameDirection(abCrossAbc, ao)) {
			return Line(points = { a, b }, direction);
		}

		else {
			if (SameDirection(abc, ao)) {
				direction = abc;
			}

			else {
				points = { a, c, b };
				direction = -abc;
			}
		}
	}

	return GL_FALSE;
}

GLboolean GJKCollisionChecker::Tetrahedron(Simplex& simplex, glm::vec3& direction)
{
	glm::vec3 a = points[0];
	glm::vec3 b = points[1];
	glm::vec3 c = points[2];
	glm::vec3 d = points[3];

	glm::vec3 ab = b - a;
	glm::vec3 ac = c - a;
	glm::vec3 ad = d - a;
	glm::vec3 ao = -a;

	glm::vec3 abc = glm::cross(ac, ab);
	glm::vec3 acd = glm::cross(ad, ac);
	glm::vec3 adb = glm::cross(ab, ad);

	if (SameDirection(abc, ao)) {
		return Triangle(points = { a, b, c }, direction);
	}

	if (SameDirection(acd, ao)) {
		return Triangle(points = { a, c, d }, direction);
	}

	if (SameDirection(adb, ao)) {
		return Triangle(points = { a, d, b }, direction);
	}

	return GL_TRUE; 
}

GLboolean GJKCollisionChecker::SameDirection(glm::vec3& direction, glm::vec3& ao)
{
	return glm::dot(ao, direction) > 0;
}