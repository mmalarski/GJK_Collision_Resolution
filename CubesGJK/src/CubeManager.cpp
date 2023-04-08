#include "CubeManager.h"

CubeManager::CubeManager()
{
	this->cubes = std::vector<Cube*>();
}

CubeManager::CubeManager(const GLuint& cubeNumber, const GLfloat& rangeOnXAxis, const GLfloat& rangeOnZAxis, const GLfloat& height)
{
	std::random_device r;
	std::default_random_engine engine(r());
	std::uniform_real_distribution<GLfloat> uniform_distX(-rangeOnXAxis, rangeOnXAxis);
	std::uniform_real_distribution<GLfloat> uniform_distZ(-rangeOnZAxis, rangeOnZAxis);

	GLfloat X = 0.0f;
	GLfloat Z = 0.0f;

	for (GLuint i = 0; i < cubeNumber; i++)
	{
		X = uniform_distX(engine);
		Z = uniform_distZ(engine);
		Cube* cube = new Cube({ X, height, Z });
		cube->setColor({ 0.98f, 0.72f, 0.01f });
		this->addCube(cube);
	}
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

void CubeManager::resolveMovement()
{
	for (Cube* cube : this->cubes)
	{
		cube->resolveMovement();
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
			.setUniform("pointLights[0]", lightManager[0].getPosition())
			.setUniform("pointLights[1]", lightManager[1].getPosition());
		cube->render();
		lightIndex++;
	}
}
