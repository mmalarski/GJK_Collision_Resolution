#include "GJKCollisionChecker.h"

GJKCollisionChecker::Simplex::Simplex()
{
	this->points = {glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f)};
	this->m_size = 0;
}

GJKCollisionChecker::Simplex& GJKCollisionChecker::Simplex::operator=(std::initializer_list<glm::vec3> list)
{
	for (auto v = list.begin(); v != list.end(); v++)
	{
		this->points[std::distance(list.begin(), v)] = *v;
	}
	this->m_size = list.size();
	return *this;
}

glm::vec3 GJKCollisionChecker::Simplex::operator[](GLuint index)
{ 
	return this->points[index]; 
}

GLuint GJKCollisionChecker::Simplex::size() 
{ 
	return this->m_size; 
}

auto GJKCollisionChecker::Simplex::begin() const
{ 
	return this->points.begin(); 
}

auto GJKCollisionChecker::Simplex::end() const
{ 
	return this->points.end() - (4 - this->m_size); 
}

void GJKCollisionChecker::Simplex::render(Shader& shader) const
{
	for (glm::vec3 vertex : this->points)
	{
		for (glm::vec3 otherVertex : this->points)
		{
			if (vertex != otherVertex)
			{
				//lineManager.addLine(new Line(vertex, otherVertex));
			}
		}
	}
}
