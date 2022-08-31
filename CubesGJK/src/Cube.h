#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Cube {
public:
	Cube();
	~Cube();
	void render();
	const GLuint getVAO();
	const GLuint getVBO();

private:
	GLuint VBO = 0, VAO = 0, EBO = 0;
	glm::vec3 vertices[8] = {
		 { 0.5f,  0.5f, 0.0f},	//A 0
		 {-0.5f,  0.5f, 0.0f},	//B 1
		 {-0.5f, -0.5f, 0.0f},	//C 2
		 { 0.5f, -0.5f, 0.0f},	//D 3
		 { 0.5f,  0.5f, 1.0f},	//E 4
		 {-0.5f,  0.5f, 1.0f},	//F 5
		 {-0.5f, -0.5f, 1.0f},	//G 6
		 { 0.5f, -0.5f, 1.0f}	//H 7
	};
	GLuint indices[36] = {
		0, 1, 2, 0, 2, 3,	  //ABC ACD
		0, 1, 5, 0, 5, 4,	  //ABF AFE
		0, 3, 7, 0, 7, 4,	  //ADH AHE
		1, 2, 6, 1, 6, 5,	  //BCG BGF
		2, 3, 7, 2, 7, 6,	  //CDH CHG
		7, 6, 5, 7, 5, 4	  //HGF HFE
	};
};