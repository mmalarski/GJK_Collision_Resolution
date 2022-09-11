#include "CubeManager.h"

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

void CubeManager::addCube(Cube* cube)
{
	this->cubes.push_back(cube);
}

const std::vector<Cube*>& CubeManager::getCubes() const
{
	return this->cubes;
}

void CubeManager::render(Shader& shader) const
{
	for (Cube* cube : this->cubes)
	{
		shader
			.use()
			.setUniform("model", cube->getModelMatrix())
			.setUniform("view", Shader::getViewMatrix())
			.setUniform("projection", Shader::getProjectionMatrix())
			.setUniform("pointLightPosition", Shader::getPointLightPosition())
			.setUniform("u_Color", cube->getColor());
		cube->render();
	}
}

CubeManager& CubeManager::setCubesHeight(const GLfloat& height)
{
	for (Cube* cube : this->cubes)
	{
		cube->setPosition(
			cube->getPosition().x,
			height,
			cube->getPosition().z
		);
	}
	return *this;
}

CubeManager& CubeManager::setCubesMovementDirection(const glm::vec3& force)
{
	for (Cube* cube : this->cubes)
	{
		cube->setMovementDirection(force);
	}
	return *this;
}

CubeManager& CubeManager::moveCubes(const GLdouble& deltaTime)
{
	for (Cube* cube : this->cubes)
	{
		if (cube->getPosition().y > 0.0f)
		{
			cube->applyGravity(deltaTime);
		}
		else
		{
			cube->setPosition(cube->getPosition().x, 0.0f, cube->getPosition().z);
		}
		cube->moveWithVector(cube->getMovementDirection());
	}
	return *this;
}
