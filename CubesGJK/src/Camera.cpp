#include "Camera.h"

Camera::Camera(const GLdouble& initialMousePositionX, const GLdouble& initialMousePositionY) :
	position(glm::vec3(0.0f, 0.0f, 3.0f)),
	front(glm::vec3(0.0f, 0.0f, -1.0f)),
	up(glm::vec3(0.0f, 1.0f, 0.0f)),
	right(glm::vec3(1.0f, 0.0f, 0.0f)),
	worldUp(this->up),
	yaw(-90.0f),
	pitch(0.0f),
	movementSpeed(0.01f),
	zoom(45.0f),
	mousePositionX(initialMousePositionX),
	mousePositionY(initialMousePositionY),
	mouseSensitivity(0.2f)
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

Camera& Camera::setMousePosition(const GLdouble& mousePositionX, const GLdouble& mousePositionY)
{
	GLdouble mouseOffsetX = mouseSensitivity * (mousePositionX - this->mousePositionX);
	GLdouble mouseOffsetY = mouseSensitivity * (this->mousePositionY - mousePositionY);

	//TODO: get rid of the gimball lock
	this->yaw += mouseOffsetX;
	this->pitch += mouseOffsetY;
	this->updateCameraVectors();

	this->mousePositionX = mousePositionX;
	this->mousePositionY = mousePositionY;
	return *this;
}

void Camera::processKeyboard(const CameraMovementDirection& direction)
{
	glm::vec3 frontOnXZPlane = glm::vec3(0.0f);
	switch (direction) {
	case FORWARD:
		frontOnXZPlane = glm::vec3(this->front.x, 0.0f, this->front.z);
		this->position += glm::normalize(frontOnXZPlane) * this->movementSpeed;
		break;
	case BACKWARD:
		frontOnXZPlane = glm::vec3(this->front.x, 0.0f, this->front.z);
		this->position -= glm::normalize(frontOnXZPlane) * this->movementSpeed;
		break;
	case LEFT:
		this->position -= this->right * this->movementSpeed;
		break;
	case RIGHT:
		this->position += this->right * this->movementSpeed;
		break;
	case UP:
		this->position += this->worldUp * this->movementSpeed;
		break;
	case DOWN:
		this->position -= this->worldUp * this->movementSpeed;
		break;
	}
}

void Camera::updateCameraVectors()
{
	glm::vec3 updatedFront;
	updatedFront.x = glm::cos(glm::radians(this->yaw)) * glm::cos(glm::radians(this->pitch));
	updatedFront.y = glm::sin(glm::radians(this->pitch));
	updatedFront.z = glm::sin(glm::radians(this->yaw)) * glm::cos(glm::radians(this->pitch));
	
	this->front = glm::normalize(updatedFront);
	this->right = glm::normalize(glm::cross(this->front, this->worldUp));
	this->up = glm::normalize(glm::cross(this->right, this->front));
}
