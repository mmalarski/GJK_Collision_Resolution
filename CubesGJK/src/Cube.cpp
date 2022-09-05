#include "Cube.h"

Cube::Cube() {
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices), this->vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &this->EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(this->indices), this->indices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

Cube::~Cube() {
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);
}

void Cube::render() {
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glColor3f(
		this->color.x, 
		this->color.y, 
		this->color.z);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

 const GLuint Cube::getVAO() const
{
	return this->VAO;
}

 const GLuint Cube::getVBO() const
{
	return this->VBO;
}

 const glm::vec4 Cube::getColor() const
 {
	 return this->color;
 }

 Cube& Cube::setColor(const glm::vec4& color)
 {
	 this->color = color;
	 return *this;
 }

 Cube& Cube::setColor(const GLfloat& r, const GLfloat& g, const GLfloat& b, const GLfloat& a)
 {
	 this->color.x = r;
	 this->color.y = g;
	 this->color.z = b;
	 this->color.w = a;
	 return *this;
 }

 Cube& Cube::setPosition(const glm::vec3& position)
 {
	 this->position = position;
	 applyPosition();
	 return *this;
 }

 Cube& Cube::setPosition(const GLfloat& x, const GLfloat& y, const GLfloat& z)
 {
	 this->position.x = x;
	 this->position.y = y;
	 this->position.z = z;
	 applyPosition();
	 return *this;
 }

 void Cube::applyPosition()
 {
	 glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	 glm::vec3 translatedVertices[CUBE_VERTICES] = { glm::vec3(0.0f) };
	 for (int i = 0; i < CUBE_VERTICES; i++)
	 {
		 translatedVertices[i] = this->vertices[i] + position;
	 }
	 glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(translatedVertices), translatedVertices);
	 glBindBuffer(GL_ARRAY_BUFFER, 0);
 }
