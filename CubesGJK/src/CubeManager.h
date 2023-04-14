#pragma once

#include "Camera.h"
#include "Cube.h"
#include <random>
#include "Shader.h"
#include <vector>

class CubeManager
{
public:
	CubeManager(const GLuint& cubeNumber, const GLfloat& rangeOnXAxis, const GLfloat& rangeOnZAxis, const GLfloat& height);
	void addCube(Cube* cube);
	const std::vector<Cube*>& getCubes() const;
	void render(Shader& shader) const;
private:
	std::vector<Cube*> cubes;
};

