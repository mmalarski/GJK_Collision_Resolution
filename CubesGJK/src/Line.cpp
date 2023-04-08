#include "Line.h"

Line::Line(glm::vec3 A, glm::vec3 B)
{
	this->setA(A);
	this->setB(B);
	this->setAColor(glm::vec3(1.0f, 1.0f, 1.0f));
	this->setBColor(glm::vec3(1.0f, 0.0f, 1.0f));
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
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->lineVertices), this->lineVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Line::setAColor(glm::vec3 color)
{
	this->lineVertices[1] = color;
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->lineVertices), this->lineVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Line::setB(glm::vec3 B)
{
	this->lineVertices[2] = B;
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->lineVertices), this->lineVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Line::setBColor(glm::vec3 color)
{
	this->lineVertices[3] = color;
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->lineVertices), this->lineVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


const glm::vec3 Line::getDirection() const
{
	return glm::normalize(this->lineVertices[2] - this->lineVertices[0]);
}

void Line::render()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
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
