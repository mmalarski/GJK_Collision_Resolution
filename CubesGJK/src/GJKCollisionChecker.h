#pragma once
#include "glm/glm.hpp"
#include "Cube.h"

class GJKCollisionChecker
{
public:
	glm::vec3 findFurthestPointOnDirection(Cube& cube, glm::vec3 direction);
	glm::vec3 findSupportPoint(Cube& cube1, Cube& cube2, glm::vec3 direction);
};

