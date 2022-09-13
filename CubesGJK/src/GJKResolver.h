#pragma once

#include "Cube.h"
#include "macros.h"
#include <array>
#include <vector>

class GJKResolver
{
public:
	GLboolean areCubesColliding(const Cube& cube1, const Cube& cube2);

private:

	struct Simplex {
	public:
		Simplex();
		Simplex& operator=(std::initializer_list<glm::vec3> list);
		glm::vec3 operator[](GLuint i);
		GLboolean isOriginInSimplex(glm::vec3& direction);
		GLuint getSize() const;
		void pushFront(const glm::vec3& point);
		auto begin() const;
		auto end() const;

	private:
		std::array<glm::vec3, 4> points;
		GLuint size;
		
		GLboolean areVectorsFacingTheSameDirection(const glm::vec3 vector1, const glm::vec3 vector2) const;
		GLboolean Line(glm::vec3& direction);
		GLboolean Triangle(glm::vec3& direction);
		GLboolean Tetrahedron(glm::vec3& direction);
	};

	glm::vec3 findSupportPointOnDirection(const Cube& cube1, const Cube& cube2, const glm::vec3& direction);
	const glm::vec3 findFurthestPointOnDirection(const Cube& cube, const glm::vec3& direction) const;
};
