#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

enum CameraMovementDirection {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Camera
{
public:
	Camera();
	const glm::mat4 getViewMatrix() const;
	const GLfloat getZoom() const;
	void processKeyboard(const CameraMovementDirection& direction, const GLfloat& deltaTime);

private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;
	GLfloat yaw;
	GLfloat pitch;
	GLfloat movementSpeed;
	GLfloat zoom;

	void updateCameraVectors();
};
