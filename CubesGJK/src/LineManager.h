#pragma once

#include "Line.h"
#include "Shader.h"
#include <vector>

class LineManager
{
public:
	LineManager();

	Line& operator[](GLuint index);
	void addLine(Line* line);
	const std::vector<Line*>& getLines() const;
	void render(Shader& shader) const;
private:
	std::vector<Line*> lines;
};

