#pragma once

#include "Cube.h"
#include "Shader.h"
#include "macros.h"

class Light
{
public:
	Light(const glm::vec3& position);
	void render(Shader& shader) const;
	void moveWithVector(const glm::vec3& direction);
	void resolveMovement();
	const glm::vec3 getPosition() const;
	
private:
	Cube cube;
};

