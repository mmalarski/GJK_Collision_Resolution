#include "Light.h"

Light::Light(const glm::vec3& position)
{
	this->cube
		.setPosition(position)
		.setColor({ 1.0f, 1.0f, 1.0f })
		.setScale(0.2f);
}

void Light::render(Shader& shader) const
{
	shader
		.setUniform("model", this->cube.getModelMatrix())
		.setUniform("u_Color", this->cube.getColor());
	this->cube.render();
}

void Light::move(const glm::vec3& direction)
{
	this->cube.moveWithVector(direction);
}

const glm::vec3 Light::getPosition() const
{
	return this->cube.getPosition();
}
