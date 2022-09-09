#include "Cube.h"

Cube::Cube() : 
	color(glm::vec4(0.4f)), 
	modelMatrix(glm::mat4(1.0f)),
	movementDirection(glm::vec3(0.0f))
{
	initializeBuffers();
}

Cube::Cube(const glm::vec3& position) : 
	color(glm::vec4(0.4f)),
	modelMatrix(glm::mat4(1.0f)),
	movementDirection(glm::vec3(0.0f))
{
	initializeBuffers();
	this->setPosition(position);
}

Cube::~Cube() {
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);
	Print("destructor");
}

void Cube::render() const {
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glDrawElements(GL_TRIANGLES, CUBE_INDICES, GL_UNSIGNED_INT, 0);
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

 const glm::mat4 Cube::getModelMatrix() const
 {
	 return this->modelMatrix;
 }

 const glm::vec3 Cube::getPosition() const
 {
	 return glm::vec3(this->modelMatrix[3][0], this->modelMatrix[3][1], this->modelMatrix[3][2]);
 }

 const glm::vec3 Cube::getMovementDirection() const
 {
	 return this->movementDirection;
 }

 Cube& Cube::setColor(const glm::vec3& color)
 {
	 this->color = glm::vec4(color.x, color.y, color.z, 1.0f);
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
	 this->modelMatrix[3][0] = position.x;
	 this->modelMatrix[3][1] = position.y;
	 this->modelMatrix[3][2] = position.z;
	 return *this;
 }

 Cube& Cube::setPosition(const GLfloat& x, const GLfloat& y, const GLfloat& z)
 {
	 this->modelMatrix[3][0] = x;
	 this->modelMatrix[3][1] = y;
	 this->modelMatrix[3][2] = z;
	 return *this;
 }

 Cube& Cube::setScale(const GLfloat& scale)
 {
	 this->modelMatrix[0][0] = scale;
	 this->modelMatrix[1][1] = scale;
	 this->modelMatrix[2][2] = scale;
	 return *this;
 }

 Cube& Cube::setMovementDirection(const glm::vec3 direction)
 {
	 this->movementDirection = direction;
	 return *this;
 }

 Cube& Cube::moveWithVector(const glm::vec3& vector) 
 {
	 this->modelMatrix = glm::translate(this->modelMatrix, vector);
	 return *this;
 }

 Cube& Cube::moveWithVector(const GLfloat& x, const GLfloat& y, const GLfloat& z)
 {
	 glm::translate(this->modelMatrix, {x, y, z});
	 return *this;
 }

 void Cube::applyGravity()
 {
	 this->movementDirection.y += -0.001f;
 }

 void Cube::initializeBuffers()
 {
	 glGenBuffers(1, &this->VBO);
	 glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	 glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices), this->vertices, GL_STATIC_DRAW);

	 glGenBuffers(1, &this->EBO);
	 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	 glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(this->indices), this->indices, GL_STATIC_DRAW);

	 glGenVertexArrays(1, &this->VAO);
	 glBindVertexArray(this->VAO);
	 glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
 }
