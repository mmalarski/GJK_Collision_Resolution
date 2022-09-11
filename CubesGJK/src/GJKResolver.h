#pragma once

#include "Cube.h"
#include "macros.h"
#include <vector>

class GJKResolver
{
public:
	glm::vec3 findSupportPointOnDirection(const Cube& cube1, const Cube& cube2, const glm::vec3& direction);
private:

	struct Simplex {
	public:
		Simplex();
		Simplex& operator=(std::initializer_list<glm::vec3> list);
		glm::vec3 operator[](GLuint i);
		void pushFront(const glm::vec3 point);
		GLuint getSize() const;
		auto begin() const;
		auto end() const;

	private:
		std::vector<glm::vec3> points;
		GLuint size;
	};

	const glm::vec3 findFurthestPointOnDirection(const Cube& cube, const glm::vec3& direction) const;
};

