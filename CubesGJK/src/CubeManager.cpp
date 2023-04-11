#include "CubeManager.h"

CubeManager::CubeManager()
{
	this->cubes = std::vector<Cube*>();
}

Cube& CubeManager::operator[](GLuint index)
{
	return *this->cubes[index];
}

void CubeManager::addCube(Cube* cube)
{
	this->cubes.push_back(cube);
}

const std::vector<Cube*>& CubeManager::getCubes() const
{
	return this->cubes;
}

void CubeManager::simulateNextMovements()
{
	for (Cube* cube : this->cubes)
	{
		cube->simulateNextMovement();
	}
}

void CubeManager::revertSimulatedMovements()
{
	for (Cube* cube : this->cubes)
	{
		cube->revertSimulatedMovement();
	}
}

void CubeManager::resetDirectionToMove()
{
	for (Cube* cube : this->cubes)
	{
		cube->resetDirectionToMove();
	}
}

void CubeManager::render(Shader& shader, LightManager& lightManager) const
{
	GLuint lightIndex = 0;
	for (Cube* cube : this->cubes)
	{
		shader
			.use()
			.setUniform("model", cube->getModelMatrix())
			.setUniform("view", Shader::getViewMatrix())
			.setUniform("projection", Shader::getProjectionMatrix())
			.setUniform("u_Color", cube->getColor())
			.setUniform("pointLights[0]", lightManager.getLights()[0]->getPosition())
			.setUniform("pointLights[1]", lightManager.getLights()[1]->getPosition());
		cube->render();
		lightIndex++;
	}
}
