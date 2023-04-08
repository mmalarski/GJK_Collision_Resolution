#pragma once

#include "Light.h"
#include "Shader.h"
#include <vector>

class LightManager
{
public:
	LightManager();
	void addLight(Light* light);
	const std::vector<Light*>& getLights() const;
	void render(Shader& shader) const;
private:
	std::vector<Light*> lights;
};

