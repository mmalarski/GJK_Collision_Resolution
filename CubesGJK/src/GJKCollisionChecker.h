#pragma once
#include <array>
#include "Colors.h"
#include "Cube.h"
#include "glm/glm.hpp"
#include "macros.h"
#include "Shader.h"
#include "Simplex.h"
#include "Line.h"

class GJKCollisionChecker
{
public:
	glm::vec3 findFurthestPointOnDirection(Cube& cube, glm::vec3 direction);
	glm::vec3 findSupportPoint(Cube& cube1, Cube& cube2, glm::vec3 direction);
	void renderSimplex(Shader& shader);
	GLboolean checkCollision(Cube& cube1, Cube& cube2);
	GLboolean nextSimplex(Simplex& simplex, glm::vec3& direction);
	void renderMinkowskiDifference(Shader& shader, Cube& cube1, Cube& cube2);
	
private:
	Simplex points;
	GLboolean Line(Simplex& simplex, glm::vec3& direction);
	GLboolean Triangle(Simplex& simplex, glm::vec3& direction);
	GLboolean Tetrahedron(Simplex& simplex, glm::vec3& direction);
	GLboolean SameDirection(glm::vec3& direction, glm::vec3& ao);
};

