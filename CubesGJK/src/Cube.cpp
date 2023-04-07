#include "Cube.h"

Cube::Cube() : 
	color(glm::vec4(0.4f)), 
	modelMatrix(glm::mat4(1.0f))
{
	initializeBuffers();
	this->directionToMove = glm::vec3(0.0f);
}

Cube::Cube(const glm::vec3& position) : 
	color(glm::vec4(0.4f)),
	modelMatrix(glm::mat4(1.0f))
{
	initializeBuffers();
	this->setPosition(position);
	this->directionToMove = glm::vec3(0.0f);
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

 const std::vector<glm::vec3> Cube::getRawVertices() const
 {
	std::vector<glm::vec3> vertices;
	vertices.push_back(glm::vec3(this->vertices[0],  this->vertices[1],  this->vertices[2]));				//A
	vertices.push_back(glm::vec3(this->vertices[6],  this->vertices[7],  this->vertices[8]));				//D
	vertices.push_back(glm::vec3(this->vertices[12],  this->vertices[13],  this->vertices[14]));			//C
	vertices.push_back(glm::vec3(this->vertices[18],  this->vertices[19],  this->vertices[20]));			//B
	vertices.push_back(glm::vec3(this->vertices[120], this->vertices[121], this->vertices[122]));			//H
	vertices.push_back(glm::vec3(this->vertices[126], this->vertices[127], this->vertices[128]));			//E
	vertices.push_back(glm::vec3(this->vertices[132], this->vertices[133], this->vertices[134]));			//F
	vertices.push_back(glm::vec3(this->vertices[138], this->vertices[139], this->vertices[140]));			//G
	return vertices;
 }

 const std::vector<glm::vec3> Cube::getTranslatedVertices() const
 {
	 std::vector<glm::vec3> vertices;
	 for (glm::vec3 vertex : this->getRawVertices())
	 {
		 vertices.push_back(glm::vec4(vertex, 1.0f) * glm::transpose(this->modelMatrix));
	 }
	 return vertices;
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

 Cube& Cube::moveWithVector(const glm::vec3& direction)
 {
	 this->directionToMove += direction;
	 return *this;
 }

 Cube& Cube::resolveMovement() 
 {
	 this->modelMatrix = glm::translate(this->modelMatrix, this->directionToMove);
	 this->directionToMove = glm::vec3(0.0f);
	 return *this;
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
