#pragma once

#include "Camera.h"
#include "Cube.h"
#include "GJKResolver.h"
#include <random>
#include "Shader.h"
#include <vector>

class CubeManager
{
public:
	CubeManager(const GLuint& cubeNumber, const GLfloat& rangeOnXAxis, const GLfloat& rangeOnZAxis, const GLfloat& height);
	const std::vector<Cube*>& getCubes() const;
	void addCube(Cube* cube);
	void resetCubeColor(Cube& cube);
	void render(Shader& shader) const;

	CubeManager& setCubesHeight(const GLfloat& height);
	CubeManager& setCubesMovementDirection(const glm::vec3& force);
	CubeManager& moveCubes(const GLdouble& deltaTime);
	CubeManager& resolveCollisions();

private:
	std::vector<Cube*> cubes;
	GJKResolver gjkResolver;
};

