#pragma once

#include "Camera.h"
#include "Cube.h"
#include "Shader.h"
#include <vector>
#include "LightManager.h"

class CubeManager
{
public:
	CubeManager();
	Cube& operator[](GLuint index);
	void addCube(Cube* cube);
	const std::vector<Cube*>& getCubes() const;
	void simulateNextMovements();
	void revertSimulatedMovements();
	void resetDirectionToMove();
	void render(Shader& shader, LightManager& lightManager) const;
private:
	std::vector<Cube*> cubes;
};

