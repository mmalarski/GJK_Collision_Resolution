#pragma once

#include "Cube.h"
#include "macros.h"
#include <array>
#include <vector>
#include <algorithm>

struct CollidingCubes
{
	Cube& cube1;
	Cube& cube2;
	glm::vec3 separationVector;

	CollidingCubes(Cube& cube1, Cube& cube2, const glm::vec3& separationVector) : cube1(cube1), cube2(cube2), separationVector(separationVector) {}
};

class GJKResolver
{
public:
	GJKResolver();
	const glm::vec3 getSeparationVector() const;
	GLboolean areCubesColliding(const Cube& cube1, const Cube& cube2);

private:

	struct Simplex {
	public:
		Simplex();
		Simplex& operator=(std::initializer_list<glm::vec3> list);
		glm::vec3 operator[](GLuint i);
		GLboolean isOriginInSimplex(glm::vec3& direction);
		GLuint getSize() const;
		const std::array<glm::vec3, 4> getSimplexPoints() const;
		void pushFront(const glm::vec3& point);
		auto begin() const;
		auto end() const;
		Simplex& sort();

	private:
		std::array<glm::vec3, 4> points;
		GLuint size;
		
		GLboolean areVectorsFacingTheSameDirection(const glm::vec3 vector1, const glm::vec3 vector2) const;
		GLboolean Line(glm::vec3& direction);
		GLboolean Triangle(glm::vec3& direction);
		GLboolean Tetrahedron(glm::vec3& direction);
	};
	glm::vec3 separationVector;

	glm::vec3 findSupportPointOnDirection(const Cube& cube1, const Cube& cube2, const glm::vec3& direction);
	const glm::vec3 findFurthestPointOnDirection(const Cube& cube, const glm::vec3& direction) const;
};
