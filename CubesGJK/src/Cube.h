#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

enum CubeInfo
{
	A,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	CUBE_VERTICES_NUMBER,
	CUBE_INDICES = 36,
	VERTEX_COMPONENTS = 3,
	VERTICES_AND_NORMALS = 2,
	NORMALS_PER_VERTEX = 3
};

class Cube {
public:
	Cube();
	Cube(const glm::vec3& position);
	~Cube();
	void render() const;
	void resetColor();
	const GLuint getVAO() const;
	const GLuint getVBO() const;
	const glm::vec4 getColor() const;
	const glm::mat4 getModelMatrix() const;
	const glm::mat4 getModelMatrixTransposed() const;
	const glm::vec3 getPosition() const;
	const glm::vec3 getMovementDirection() const;
	const glm::vec3* getVertices() const;
	Cube& setColor(const glm::vec3& color);
	Cube& setColor(const GLfloat& r, const GLfloat& g, const GLfloat& b, const GLfloat& a);
	Cube& setPosition(const glm::vec3& position);
	Cube& setPosition(const GLfloat& x, const GLfloat& y, const GLfloat& z);
	Cube& setScale(const GLfloat& scale);
	Cube& setMovementDirection(const glm::vec3 direction);
	Cube& moveWithVector(const glm::vec3& vector);
	Cube& moveWithVector(const GLfloat& x, const GLfloat& y, const GLfloat& z);
	void applyGravity(const GLdouble& deltaTime);

private:
	GLuint VBO = 0, VAO = 0, EBO = 0;
	glm::vec3 vertices[CUBE_VERTICES_NUMBER] = {
		{  0.5f,  0.5f, -0.5f },	//A 0
		{ -0.5f,  0.5f, -0.5f },	//B 1
		{ -0.5f, -0.5f, -0.5f },	//C 2
		{  0.5f, -0.5f, -0.5f },	//D 3

		{  0.5f,  0.5f,  0.5f },	//E 4
		{ -0.5f,  0.5f,  0.5f },	//F 5
		{ -0.5f, -0.5f,  0.5f },	//G 6
		{  0.5f, -0.5f,  0.5f }		//H 7
	};
	GLfloat verticesAndNormals[CUBE_VERTICES_NUMBER * VERTEX_COMPONENTS * VERTICES_AND_NORMALS * NORMALS_PER_VERTEX] = {
		vertices[A].x, vertices[A].y, vertices[A].z,  0.0f,  0.0f, -1.0f,	//A 0
		vertices[D].x, vertices[D].y, vertices[D].z,  0.0f,  0.0f, -1.0f,	//D 1
		vertices[C].x, vertices[C].y, vertices[C].z,  0.0f,  0.0f, -1.0f,	//C 2
		vertices[B].x, vertices[B].y, vertices[B].z,  0.0f,  0.0f, -1.0f,	//B 3
							   								 
		vertices[A].x, vertices[A].y, vertices[A].z,  0.0f,  1.0f,  0.0f,	//A 4
		vertices[B].x, vertices[B].y, vertices[B].z,  0.0f,  1.0f,  0.0f,	//B 5
		vertices[F].x, vertices[F].y, vertices[F].z,  0.0f,  1.0f,  0.0f,	//F 6
		vertices[E].x, vertices[E].y, vertices[E].z,  0.0f,  1.0f,  0.0f,	//E 7
							   								 	   
		vertices[A].x, vertices[A].y, vertices[A].z,  1.0f,  0.0f,  0.0f,	//A 8
		vertices[E].x, vertices[E].y, vertices[E].z,  1.0f,  0.0f,  0.0f,	//E 9
		vertices[H].x, vertices[H].y, vertices[H].z,  1.0f,  0.0f,  0.0f,	//H 10
		vertices[D].x, vertices[D].y, vertices[D].z,  1.0f,  0.0f,  0.0f,	//D 11
															 
		vertices[B].x, vertices[B].y, vertices[B].z, -1.0f,  0.0f,  0.0f,	//B 12
		vertices[C].x, vertices[C].y, vertices[C].z, -1.0f,  0.0f,  0.0f,	//C 13
		vertices[G].x, vertices[G].y, vertices[G].z, -1.0f,  0.0f,  0.0f,	//G 14
		vertices[F].x, vertices[F].y, vertices[F].z, -1.0f,  0.0f,  0.0f,	//F 15
																   
		vertices[C].x, vertices[C].y, vertices[C].z,  0.0f, -1.0f,  0.0f,	//C 16
		vertices[D].x, vertices[D].y, vertices[D].z,  0.0f, -1.0f,  0.0f,	//D 19
		vertices[H].x, vertices[H].y, vertices[H].z,  0.0f, -1.0f,  0.0f,	//H 18
		vertices[G].x, vertices[G].y, vertices[G].z,  0.0f, -1.0f,  0.0f,	//G 17
							   									   
		vertices[H].x, vertices[H].y, vertices[H].z,  0.0f,  0.0f,  1.0f,	//H 20
		vertices[E].x, vertices[E].y, vertices[E].z,  0.0f,  0.0f,  1.0f,	//E 21
		vertices[F].x, vertices[F].y, vertices[F].z,  0.0f,  0.0f,  1.0f,	//F 22
		vertices[G].x, vertices[G].y, vertices[G].z,  0.0f,  0.0f,  1.0f	//G 23
	};
	GLuint indices[CUBE_INDICES] = {
		0,   1,  2,  0,  2,  3,	  //ADC ACB
		4,   5,  6,  4,  6,  7,	  //ABF AFE
		8,   9, 10,  8, 10, 11,	  //AEH AHD
		12, 13, 14, 12, 14, 15,	  //BCG BGF
		16, 17, 18, 16, 18, 19,	  //CDH CHG
		20, 21, 22, 20, 22, 23	  //HEF HFG
	};
	glm::vec4 color;
	glm::mat4 modelMatrix;
	glm::mat4 modelMatrixTransposed;
	glm::vec3 movementDirection;

	void initializeBuffers();
};