#include "Camera.h"

Camera::Camera()
{
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	this->yaw = -90.0f;
	this->pitch = 5.0f;
	this->movingSpeed = 5.0;
	this->rotatingSpeed = 4.0;
	this->isMouvmentActive = true;
	updateCameraVectors();
}

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float movingSpeed, float rotatingSpeed)
{
	this->position = position;
	this->worldUp = up;
	this->yaw = yaw;
	this->pitch = pitch;
	this->movingSpeed = movingSpeed;
	this->rotatingSpeed = rotatingSpeed;
	this->isMouvmentActive = true;

}

Camera::~Camera()
{
}

void Camera::keyControl(bool* keys, float deltaTime)
{
	float velocity = movingSpeed * deltaTime;

	//If it's a space 
	if (!this->isMouvmentActive)
	{
		return;
	}
	if (keys[GLFW_KEY_W])
	{
		position += front * velocity;
	}
	if (keys[GLFW_KEY_S])
	{
		position -= front * velocity;
	}
	if (keys[GLFW_KEY_A])
	{
		position -= right * velocity;
	}
	if (keys[GLFW_KEY_D])
	{
		position += right * velocity;
	}

	if (keys[GLFW_KEY_Q])
	{
		position -= up * velocity;
	}

	if (keys[GLFW_KEY_E])
	{
		position += up * velocity;
	}

	if (keys[GLFW_KEY_LEFT_SHIFT])
	{
		movingSpeed = 10.0f;

	}
	else if (keys[GLFW_KEY_LEFT_CONTROL])
	{
		movingSpeed = 1.0f;
	}
	else
	{
		movingSpeed = 5.0f;
	}
}

void Camera::mouseControl(float xChange, float yChange)
{
	if (!isMouvmentActive)
	{
		return;
	}
	xChange *= rotatingSpeed;
	yChange *= rotatingSpeed;

	yaw += xChange;
	pitch += yChange;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}

	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	updateCameraVectors();
}

glm::mat4 Camera::calculateViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

void Camera::updateCameraVectors()
{
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	this->front = glm::normalize(front);
	this->right = glm::normalize(glm::cross(this->front, this->worldUp));
	this->up = glm::normalize(glm::cross(this->right, this->front));
}
