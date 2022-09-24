#include "GJKResolver.h"

GJKResolver::Simplex::Simplex()
{
	this->points = { glm::vec3(0.0f) };
	this->size = 0;
}

GJKResolver::Simplex& GJKResolver::Simplex::operator=(std::initializer_list<glm::vec3> list)
{
	for (auto point = list.begin(); point != list.end(); point++)
	{
		this->points[std::distance(list.begin(), point)] = *point;
	}
	this->size = list.size();
	return *this;
}

glm::vec3 GJKResolver::Simplex::operator[](GLuint i)
{
	return this->points[i];
};

GLboolean GJKResolver::Simplex::isOriginInSimplex(glm::vec3& direction)
{
	switch (this->getSize())
	{
	case 2: return this->Line(direction);
	case 3: return this->Triangle(direction);
	case 4: return this->Tetrahedron(direction);
	}

	return false;
}

void GJKResolver::Simplex::pushFront(const glm::vec3& point)
{
	this->points = { point, this->points[0], this->points[1], this->points[2] };
	this->size = glm::min(this->size + 1, 4u);
}

GLuint GJKResolver::Simplex::getSize() const
{
	return this->size;
}

const std::array<glm::vec3, 4> GJKResolver::Simplex::getSimplexPoints() const
{
	return this->points;
}

auto GJKResolver::Simplex::begin() const
{
	return this->points.begin();
}

auto GJKResolver::Simplex::end() const
{
	return this->points.end();
}

GLboolean GJKResolver::Simplex::areVectorsFacingTheSameDirection(const glm::vec3 vector1, const glm::vec3 vector2) const
{
	return glm::dot(vector1, vector2) > 0;
}

GLboolean GJKResolver::Simplex::Line(glm::vec3& direction)
{
	glm::vec3 a = this->points[0];
	glm::vec3 b = this->points[1];

	glm::vec3 ab = b - a;
	glm::vec3 a0 =   - a;

	if (this->areVectorsFacingTheSameDirection(ab, a0))
	{
		direction = glm::cross(ab, glm::cross(ab, a0));
	} 
	else
	{
		this->points = { a };
		direction = a0;
	}

	return false;
}

GLboolean GJKResolver::Simplex::Triangle(glm::vec3& direction)
{
	glm::vec3 a = this->points[0];
	glm::vec3 b = this->points[1];
	glm::vec3 c = this->points[2];

	glm::vec3 ab = b - a;
	glm::vec3 ac = c - a;
	glm::vec3 a0 =   - a;

	glm::vec3 abc = glm::cross(ab, ac);

	if (this->areVectorsFacingTheSameDirection(glm::cross(abc, ac), a0))
	{
		if (this->areVectorsFacingTheSameDirection(ac, a0))
		{
			this->points = { a, c };
			direction = glm::cross(ac, glm::cross(ac, a0));
		}
		else
		{
			this->points = { a, b };
			return Line(direction);
		}
	}
	else
	{
		if (this->areVectorsFacingTheSameDirection(glm::cross(ab, abc), a0))
		{
			this->points = { a, b };
			return Line(direction);
		}
		else
		{
			if (this->areVectorsFacingTheSameDirection(abc, a0))
			{
				direction = abc;
			}
			else
			{
				this->points = { a, c, b };
				direction = -abc;
			}
		}
	}
	return false;
}

GLboolean GJKResolver::Simplex::Tetrahedron(glm::vec3& direction)
{
	glm::vec3 a = this->points[0];
	glm::vec3 b = this->points[1];
	glm::vec3 c = this->points[2];
	glm::vec3 d = this->points[3];

	glm::vec3 ab = b - a;
	glm::vec3 ac = c - a;
	glm::vec3 ad = d - a;
	glm::vec3 ao =   - a;

	glm::vec3 abc = glm::cross(ab, ac);
	glm::vec3 acd = glm::cross(ac, ad);
	glm::vec3 adb = glm::cross(ad, ab);

	if (this->areVectorsFacingTheSameDirection(abc, ao)) {
		this->points = { a, b, c };
		return Triangle(direction);
	}

	if (this->areVectorsFacingTheSameDirection(acd, ao)) {
		this->points = { a, c, d };
		return Triangle(direction);
	}

	if (this->areVectorsFacingTheSameDirection(adb, ao)) {
		this->points = { a, d, b };
		return Triangle(direction);
	}

	return true;
}

GJKResolver::Simplex& GJKResolver::Simplex::sort()
{
	std::sort(this->points.begin(), this->points.end(), [](glm::vec3 p1, glm::vec3 p2)
		{
			return glm::length(p1) < glm::length(p2);
		});
	return *this;
}
