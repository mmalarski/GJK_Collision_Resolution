#pragma once
#include <array>
#include "Colors.h"
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "Line.h"
#include "Shader.h"

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