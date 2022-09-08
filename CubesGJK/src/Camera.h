#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include "macros.h"

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
	Camera(const GLdouble& initialMousePositionX, const GLdouble& initialMousePositionY);
	const glm::vec3 getPosition() const;
	const glm::mat4 getViewMatrix() const;
	const GLfloat getZoom() const;
	Camera& setMousePosition(const GLdouble& mousePositionX, const GLdouble& mousePositionY);
	void processKeyboard(const CameraMovementDirection& direction);

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

	GLdouble mousePositionX;
	GLdouble mousePositionY;
	GLfloat mouseSensitivity;

	void updateCameraVectors();
};
