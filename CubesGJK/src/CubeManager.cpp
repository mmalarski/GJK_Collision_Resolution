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

CubeManager::CubeManager(const GLuint& rowsNumber, const GLuint& columnsNumber, const GLfloat& height)
{
	for (GLuint i = 0; i < rowsNumber; i++)
	{
		for (GLuint j = 0; j < columnsNumber; j++)
		{
			Cube* cube = new Cube({ 2*i, height, 2*j });
			cube->setColor({ 0.98f, 0.72f, 0.01f });
			this->addCube(cube);
		}
	}

	for (Cube* cube : this->cubes)
	{
		cube->moveWithVector(glm::vec3(rowsNumber * -0.5f, 0.0f, columnsNumber * -0.5f));
	}
}

CubeManager& CubeManager::addCube(Cube* cube)
{
	this->cubes.push_back(cube);
	return *this;
}

void CubeManager::resetCubeColor(Cube& cube)
{
	cube.setColor({ 0.98f, 0.72f, 0.01f });
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

CubeManager& CubeManager::setCubesNextMovementVector(const glm::vec3& vector)
{
	for (Cube* cube : this->cubes)
	{
		cube->setNextMovementVector(vector);
	}
	return *this;
}

CubeManager& CubeManager::setCubesForceVector(const glm::vec3& vector)
{
	for (Cube* cube : this->cubes)
	{
		cube->setForceVector(vector);
	}
	return *this;
}

CubeManager& CubeManager::launchCubes()
{
	std::random_device r;
	std::default_random_engine engine(r());
	std::uniform_real_distribution<GLfloat> uniform_distX(-0.01f, 0.01f);
	std::uniform_real_distribution<GLfloat> uniform_distY(0.0f, 0.06f);
	std::uniform_real_distribution<GLfloat> uniform_distZ(-0.01f, 0.01f);
	for (Cube* cube : this->cubes)
	{
		cube->setForceVector({uniform_distX(engine), uniform_distY(engine), uniform_distZ(engine) });
	}
	return *this;
}

CubeManager& CubeManager::applyCubesNextMovementVectors(const GLint64& elapsedTime)
{
	for (Cube* cube : this->cubes)
	{
		if (cube->getPosition().y > 0.0f)
		{
			cube->applyGravity(elapsedTime);
		}
		else if (cube->getPosition().y != 0.0f)
		{
			cube->setPosition(cube->getPosition().x, 0.0f, cube->getPosition().z);
			cube->setGravityVector(glm::vec3(0.0f));
			cube->setForceVector(glm::vec3(0.0f));
		}
		cube->applyNextMovementVectors();
	}
	return *this;
}

CubeManager& CubeManager::resolveCollisions(const GLint64& elapsedTime)
{
	for (Cube* cube1 : this->cubes)
	{
		for (Cube* cube2 : this->cubes)
		{
			if (cube1 != cube2)
			{
				if (this->gjkResolver.areCubesNotColliding(cube1->simulateNextPosition(), cube2->simulateNextPosition()))
				{
					this->applyCubesNextMovementVectors(elapsedTime);
				}
			}
		}
	}
	return *this;
}
