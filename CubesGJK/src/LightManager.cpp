#include "LightManager.h"

LightManager::LightManager()
{
	this->lights = std::vector<Light*>();
}

void LightManager::addLight(Light* light)
{
	this->lights.push_back(light);
}

const std::vector<Light*>& LightManager::getLights() const
{
	return this->lights;
}

void LightManager::render(Shader& shader) const
{
	for (Light* light : this->lights)
	{
		light->render(shader);
	}
}
