#pragma once

#include "Cube.h"
#include "macros.h"

class GJKResolver
{
public:
	glm::vec3 findSupportPointOnDirection(const Cube& cube1, const Cube& cube2, const glm::vec3& direction);
private:
	const glm::vec3 findFurthestPointOnDirection(const Cube& cube, const glm::vec3& direction) const;
};

