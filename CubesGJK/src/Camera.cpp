#include "Camera.h"

Camera::Camera():
	position(glm::vec3(0.0f)),
	front(glm::vec3(0.0f, 0.0f, -1.0f)),
	up(glm::vec3(0.0f, 1.0f, 0.0f)),
	right(glm::vec3(1.0f, 0.0f, 0.0f)),
	worldUp(this->up),
	yaw(0.0f),
	pitch(0.0f),
	movementSpeed(0.01f),
	zoom(45.0f)
{
	updateCameraVectors();
}

const glm::vec3 Camera::getPosition() const
{
	return this->position;
}

const glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(this->position, this->position + this->front, this->up);
}

const GLfloat Camera::getZoom() const
{
	return this->zoom;
}

void Camera::processKeyboard(const CameraMovementDirection& direction)
{
	switch (direction) {
	case FORWARD:
		this->position += this->front * this->movementSpeed;
		break;
	case BACKWARD:
		this->position -= this->front * this->movementSpeed;
		break;
	case LEFT:
		this->position -= this->right * this->movementSpeed;
		break;
	case RIGHT:
		this->position += this->right * this->movementSpeed;
		break;
	case UP:
		this->position += this->up * this->movementSpeed;
		break;
	case DOWN:
		this->position -= this->up * this->movementSpeed;
		break;
	}
	printf("Cameras position: %f, %f, %f\n", this->position.x, this->position.y, this->position.z);
}

void Camera::updateCameraVectors()
{
	glm::vec3 updatedFront;
	updatedFront.x = glm::cos(glm::radians(this->yaw) * glm::cos(glm::radians(this->pitch)));
	updatedFront.y = glm::sin(glm::radians(this->pitch));
	updatedFront.z = glm::sin(glm::radians(this->yaw) * glm::cos(glm::radians(this->pitch)));
	this->front = glm::normalize(updatedFront);
	this->right = glm::normalize(glm::cross(this->front, this->worldUp));
	this->up = glm::normalize(glm::cross(this->right, this->front));
}