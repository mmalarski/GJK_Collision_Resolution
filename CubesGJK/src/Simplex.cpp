#include "Simplex.h"

Simplex::Simplex()
{
	this->points = {glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f)};
	this->m_size = 0;
}

Simplex& Simplex::operator=(std::initializer_list<glm::vec3> list)
{
	for (auto v = list.begin(); v != list.end(); v++)
	{
		this->points[std::distance(list.begin(), v)] = *v;
	}
	this->m_size = list.size();
	return *this;
}

void Simplex::pushFront(glm::vec3 point)
{
	this->points = { point, this->points[0], this->points[1], this->points[2] };
	this->m_size = std::min(m_size + 1, 4u);
}

glm::vec3 Simplex::operator[](GLuint index)
{ 
	return this->points[index]; 
}

GLuint Simplex::size() 
{ 
	return this->m_size; 
}

auto Simplex::begin() const
{ 
	return this->points.begin(); 
}

auto Simplex::end() const
{ 
	return this->points.end() - (4 - this->m_size); 
}

void Simplex::render(Shader& shader) const
{
	for (glm::vec3 vertex : this->points)
	{
		for (glm::vec3 otherVertex : this->points)
		{
			if (vertex != otherVertex)
			{
				Line::drawLine(shader, vertex, Colors::Cyan, otherVertex, Colors::Cyan);
			}
		}
	}
}
