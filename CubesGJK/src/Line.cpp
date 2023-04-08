#include "Line.h"

GLuint Line::VAO, Line::VBO;
glm::vec3 Line::lineVertices[4] = {
	glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),
	glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)
};

void Line::init()
{
    // Create the vertex array object (VAO)
    glGenVertexArrays(1, &Line::VAO);
    glBindVertexArray(Line::VAO);

    // Create the vertex buffer object (VBO)
    glGenBuffers(1, &Line::VBO);
    glBindBuffer(GL_ARRAY_BUFFER, Line::VBO);
}

void Line::drawLine(Shader& shader, glm::vec3 A, glm::vec3& AColor, glm::vec3 B, glm::vec3& BColor)
{
    shader
        .use()
		.setUniform("view", Shader::getViewMatrix())
		.setUniform("projection", Shader::getProjectionMatrix());

    // Update the vertices of the line
    lineVertices[0] = A;
	lineVertices[1] = AColor;
    lineVertices[2] = B;
	lineVertices[3] = BColor;

    // Upload the vertices to the GPU
    glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices), lineVertices, GL_DYNAMIC_DRAW);

    // Enable the vertex attribute array for the vertex position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Render the line
    glDrawArrays(GL_LINES, 0, 2);
}

void Line::cleanUp()
{
    // Clean up the VBO and VAO
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &Line::VBO);
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &Line::VBO);
}
