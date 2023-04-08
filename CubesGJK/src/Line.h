#pragma once

#include "glm/glm.hpp"
#include <GL/glew.h>
#include "Shader.h"

class Line
{
public:
	static void init();
	static void drawLine(Shader& shader, glm::vec3 A, glm::vec3& AColor, glm::vec3 B, glm::vec3& BColor);
	static void cleanUp();
private:
	static GLuint VAO, VBO;
	static glm::vec3 lineVertices[4];
};