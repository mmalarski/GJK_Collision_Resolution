#include "Camera.h"

Camera::Camera()
{
	this->position = glm::vec3(0.0f);
	this->front = glm::vec3(0.0f, 0.0f, -1.0f);
	this->up = glm::vec3(0.0f, 1.0f, 0.0f);
	this->worldUp = this->up;
	updateCameraVectors();
}

const glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(this->position, this->position + this->front, this->up);
}

const GLfloat Camera::getZoom() const
{
	return this->zoom;
}

void Camera::processKeyboard(const CameraMovementDirection& direction, const GLfloat& deltaTime)
{
	GLfloat velocity = this->movementSpeed * deltaTime;
	switch (direction) {
	case CameraMovementDirection::FORWARD:
		this->position += this->front * velocity;
	case CameraMovementDirection::BACKWARD:
		this->position -= this->front * velocity;
	case CameraMovementDirection::LEFT:
		this->position -= this->right * velocity;
	case CameraMovementDirection::RIGHT:
		this->position += this->right * velocity;
	case CameraMovementDirection::UP:
		this->position += this->up * velocity;
	case CameraMovementDirection::DOWN:
		this->position -= this->up * velocity;
	}
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