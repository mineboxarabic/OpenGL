#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
class Camera
{
	public:
	Camera();
	Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float movingSpeed, float rotatingSpeed);

	~Camera();

	void keyControl(bool* keys, float deltaTime);
	void mouseControl(float xChange, float yChange);

	glm::mat4 calculateViewMatrix();

	glm::vec3 getCameraPosition() { return position; }
	glm::vec3 getCameraDirection() { return glm::normalize(front); }



private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;
	bool isMouvmentActive;

	float yaw;
	float pitch;

	float movingSpeed;
	float rotatingSpeed;

	void updateCameraVectors();
};

