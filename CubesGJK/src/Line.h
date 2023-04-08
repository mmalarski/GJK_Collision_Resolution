#pragma once
#include "glm/glm.hpp"
#include <GL/glew.h>
#include <vector>
#include "iostream"
#include "macros.h"

class Line
{
public:
	Line(glm::vec3 A, glm::vec3 B);
	~Line();
	void setA(glm::vec3 A);
	void setB(glm::vec3 B);
	void render();
	
private:
	void initializeBuffers();
	GLuint VBO, VAO;
	glm::vec3 lineVertices[2] = {
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 0.0f)
	};
};

