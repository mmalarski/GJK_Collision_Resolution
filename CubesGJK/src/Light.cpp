#include "Light.h"

Light::Light(const glm::vec3& position)
{
	this->cube
		.setPosition(position)
		.setColor({ 1.0f, 1.0f, 1.0f })
		.setScale(0.05f);
}

void Light::render(Shader& shader) const
{
	shader
		.use()
		.setUniform("view", Shader::getViewMatrix())
		.setUniform("projection", Shader::getProjectionMatrix())
		.setUniform("model", this->cube.getModelMatrix());
	this->cube.render();
}

void Light::moveWithVector(const glm::vec3& direction)
{
	this->cube.moveWithVector(direction);
}

void Light::setPosition(glm::vec3 position)
{
	this->cube.setPosition(position);
}

void Light::resolveMovement()
{
	this->cube.resolveMovement();
}

const glm::vec3 Light::getPosition() const
{
	return this->cube.getPosition();
}
