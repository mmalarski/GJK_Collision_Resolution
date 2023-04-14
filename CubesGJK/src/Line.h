#pragma once

#include "glm/glm.hpp"
#include <GL/glew.h>
#include "Shader.h"

class Line
{
public:
	static void drawLine(Shader& shader, glm::vec3 A, glm::vec3& AColor, glm::vec3 B, glm::vec3& BColor);
private:
	static glm::vec3 lineVertices[4];
};