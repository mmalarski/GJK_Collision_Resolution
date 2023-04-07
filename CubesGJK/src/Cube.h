#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "macros.h"
#include <iostream>

#define CUBE_VERTICES	8
#define CUBE_INDICES	36
#define VERTEX_COMPONENTS 3
#define VERTICES_AND_NORMALS 2
#define NORMALS_PER_VERTEX 3

class Cube {
public:
	Cube();
	Cube(const glm::vec3& position);
	~Cube();
	void render() const;
	const GLuint getVAO() const;
	const GLuint getVBO() const;
	const glm::vec4 getColor() const;
	const glm::mat4 getModelMatrix() const;
	const glm::vec3 getPosition() const;
	Cube& setColor(const glm::vec3& color);
	Cube& setColor(const GLfloat& r, const GLfloat& g, const GLfloat& b, const GLfloat& a);
	Cube& setPosition(const glm::vec3& position);
	Cube& setPosition(const GLfloat& x, const GLfloat& y, const GLfloat& z);
	Cube& setScale(const GLfloat& scale);
	Cube& moveWithVector(const glm::vec3& direction);
	Cube& resolveMovement();

private:
	GLuint VBO = 0, VAO = 0, EBO = 0;
	GLfloat vertices[CUBE_VERTICES * VERTEX_COMPONENTS * VERTICES_AND_NORMALS * NORMALS_PER_VERTEX] = {
		  0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,	//A 0
		  0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,	//D 1
		 -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,	//C 2
		 -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,	//B 3
							   
		  0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,	//A 4
		 -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,	//B 5
		 -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,	//F 6
		  0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,	//E 7
							   
		  0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,	//A 8
		  0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,	//E 9
		  0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,	//H 10
		  0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,	//D 11
		
		 -0.5f,  0.5f, -0.5f, -1.0f, 0.0f, 0.0f,	//B 12
		 -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,	//C 13
		 -0.5f, -0.5f,  0.5f, -1.0f, 0.0f, 0.0f,	//G 14
		 -0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f,	//F 15
													
		 -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,	//C 16
		  0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,	//D 19
		  0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f,	//H 18
		 -0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f,	//G 17
							   
		  0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,	//H 20
		  0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 	//E 21
		 -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,	//F 22
		 -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,	//G 23
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
	glm::vec3 directionToMove;

	void initializeBuffers();
};