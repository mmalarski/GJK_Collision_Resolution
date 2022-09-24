#include "Cube.h"

Cube::Cube() : 
	color(glm::vec4(0.4f)), 
	modelMatrix(glm::mat4(1.0f)),
	nextMovementVector(glm::vec3(0.0f)),
	currentGravityVector(glm::vec3(0.0f)),
	currentForceVector(glm::vec3(0.0f))
{
	initializeBuffers();
}

Cube::Cube(const glm::vec3& position) : 
	color(glm::vec4(0.4f)),
	modelMatrix(glm::mat4(1.0f)),
	nextMovementVector(glm::vec3(0.0f)),
	currentGravityVector(glm::vec3(0.0f)),
	currentForceVector(glm::vec3(0.0f))
{
	initializeBuffers();
	this->setPosition(position);
}

Cube::~Cube() {
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);
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

 const glm::vec3 Cube::getNextMovementVector() const
 {
	 return this->nextMovementVector;
 }

 const glm::vec3* Cube::getVertices() const
 {
	 return this->vertices;
 }

 const glm::vec3 Cube::getCurrentGravityVector() const
 {
	 return this->currentGravityVector;
 }

 const glm::vec3 Cube::getCurrentForceVector() const
 {
	 return this->currentForceVector;
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

 Cube& Cube::setNextMovementVector(const glm::vec3& vector)
 {
	 this->nextMovementVector = vector;
	 return *this;
 }

 Cube& Cube::setGravityVector(const glm::vec3& vector)
 {
	 this->currentGravityVector = vector;
	 return *this;
 }

 Cube& Cube::setForceVector(const glm::vec3& vector)
 {
	 this->currentForceVector = vector;
	 return *this;
 }

 void Cube::addToNextMovementVector(const glm::vec3& vector)
 {
	 this->nextMovementVector += vector;
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

 void Cube::applyGravity(const GLint64& elapsedTime)
 {
	 this->currentGravityVector.y += -0.00001 * elapsedTime;
	 Print(elapsedTime);
 }

 void Cube::applyNextMovementVectors()
 {
	 this->setPosition(this->getPosition() + this->nextMovementVector + this->currentGravityVector + this->currentForceVector);
	 this->nextMovementVector = glm::vec3(0.0f);
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
