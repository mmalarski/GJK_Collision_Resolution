#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define CUBE_VERTICES	8
#define CUBE_INDICES	36

class Cube {
public:
	Cube();
	~Cube();
	void render();
	GLuint getVAO() const;
	GLuint getVBO() const;
	Cube& setColor(glm::vec3 color);
	Cube& setColor(GLfloat r, GLfloat g, GLfloat b);
	Cube& setPosition(glm::vec3 position);
	Cube& setPosition(GLfloat x, GLfloat y, GLfloat z);
	const GLuint getVAO() const;
	const GLuint getVBO() const;
	const glm::vec4 getColor() const;
	Cube& setColor(const glm::vec4& color);

private:
	GLuint VBO = 0, VAO = 0, EBO = 0;
	glm::vec3 vertices[CUBE_VERTICES] = {
		 { 0.5f,  0.5f, 0.0f},	//A 0
		 {-0.5f,  0.5f, 0.0f},	//B 1
		 {-0.5f, -0.5f, 0.0f},	//C 2
		 { 0.5f, -0.5f, 0.0f},	//D 3
		 { 0.5f,  0.5f, 1.0f},	//E 4
		 {-0.5f,  0.5f, 1.0f},	//F 5
		 {-0.5f, -0.5f, 1.0f},	//G 6
		 { 0.5f, -0.5f, 1.0f}	//H 7
	};
	GLuint indices[CUBE_INDICES] = {
		0, 1, 2, 0, 2, 3,	  //ABC ACD
		0, 1, 5, 0, 5, 4,	  //ABF AFE
		0, 3, 7, 0, 7, 4,	  //ADH AHE
		1, 2, 6, 1, 6, 5,	  //BCG BGF
		2, 3, 7, 2, 7, 6,	  //CDH CHG
		7, 6, 5, 7, 5, 4	  //HGF HFE
	};
	glm::vec3 color = glm::vec3(0.2f);
	glm::vec3 position = glm::vec3(0.0f);

	void applyPosition();
	glm::vec4 color = glm::vec4(0.0f);
};