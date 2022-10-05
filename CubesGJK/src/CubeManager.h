#pragma once

#include "Camera.h"
#include "Cube.h"
#include "GJKResolver.h"
#include <random>
#include "Shader.h"
#include <vector>
#include <set>

class CubeManager
{
public:
	CubeManager(const GLuint& cubeNumber, const GLfloat& rangeOnXAxis, const GLfloat& rangeOnZAxis, const GLfloat& height);
	CubeManager(const GLuint& rowsNumber, const GLuint& columnsNumber, const GLfloat& height);
	const std::vector<Cube*>& getCubes() const;
	CubeManager& addCube(Cube* cube);
	void resetCubeColor(Cube& cube);
	void render(Shader& shader) const;

	CubeManager& setCubesHeight(const GLfloat& height);
	CubeManager& setCubesNextMovementVector(const glm::vec3& vector);
	CubeManager& setCubesForceVector(const glm::vec3& vector);
	CubeManager& launchCubes();
	CubeManager& applyCubesNextMovementVectors(const GLint64& elapsedTime);
	CubeManager& resolveCollisions(const GLint64& elapsedTime);

private:
	std::vector<Cube*> cubes;
	GJKResolver gjkResolver;
};

