#pragma once
#include "glm/glm.hpp"
#include "Cube.h"
#include <array>
#include "Shader.h"
#include "Line.h"

class GJKCollisionChecker
{
public:
	glm::vec3 findFurthestPointOnDirection(Cube& cube, glm::vec3 direction);
	glm::vec3 findSupportPoint(Cube& cube1, Cube& cube2, glm::vec3 direction);
	void renderSimplex(Shader& shader);
	
private:
	struct Simplex
	{
	public:
		Simplex();
		Simplex& operator=(std::initializer_list<glm::vec3> list);
		void pushFront(glm::vec3 point);
		glm::vec3 operator[](GLuint index);
		GLuint size();
		auto begin() const;
		auto end() const;
		void render(Shader& shader) const;
			
	private:
		std::array<glm::vec3, 4> points;
		GLuint m_size;
	};
	Simplex points;
};

