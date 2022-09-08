#pragma once

#include "Cube.h"
#include "Shader.h"
#include "macros.h"

class Light
{
public:
	Light(const glm::vec3& position);
	void render(Shader& shader) const;
	void move(const glm::vec3& direction);
	const glm::vec3 getPosition() const;
	
private:
	Cube cube;
};

