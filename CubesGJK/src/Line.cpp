#include "Line.h"

Line::Line(glm::vec3 A, glm::vec3 B)
{
	this->setA(A);
	this->setB(B);
	this->VAO = 0;
	this->VBO = 0;
	initializeBuffers();
}

Line::~Line()
{
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
}

void Line::setA(glm::vec3 A)
{
	this->lineVertices[0] = A;
}

void Line::setB(glm::vec3 B)
{
	this->lineVertices[1] = B;
}

void Line::render()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_LINES, 0, 2);
}

void Line::initializeBuffers()
{
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->lineVertices), this->lineVertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
}
