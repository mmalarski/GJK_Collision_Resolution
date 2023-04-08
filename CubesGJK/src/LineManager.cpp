#include "LineManager.h"

LineManager::LineManager()
{
	this->lines = std::vector<Line*>();
}

void LineManager::addLine(Line* line)
{
	this->lines.push_back(line);
}

const std::vector<Line*>& LineManager::getLines() const
{
	return this->lines;
}

void LineManager::render(Shader& shader) const
{
	for (Line* line : this->lines)
	{
		shader
			.use()
			.setUniform("view", Shader::getViewMatrix())
			.setUniform("projection", Shader::getProjectionMatrix());
		line->render();
	}
}
