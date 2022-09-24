#pragma once

#include "Camera.h"
#include "Cube.h"
#include <random>
#include "Shader.h"
#include <vector>
#include <set>

class CubeManager
{
public:
	CubeManager(const GLuint& cubeNumber, const GLfloat& rangeOnXAxis, const GLfloat& rangeOnZAxis, const GLfloat& height);
	const std::vector<Cube*>& getCubes() const;
	CubeManager& addCube(Cube* cube);
	void resetCubeColor(Cube& cube);
	void render(Shader& shader) const;
	CubeManager& setCubesHeight(const GLfloat& height);
	CubeManager& setCubesNextMovementVector(const glm::vec3& vector);
	CubeManager& setCubesForceVector(const glm::vec3& vector);
	CubeManager& moveCubes(const GLint64& elapsedTime);
	CubeManager& resolveCollisions();

private:
	std::vector<Cube*> cubes;
};

