#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <intrin.h>
#include <iostream>
class Window
{
	public:
	Window();
	Window(int width, int height, const char* title);
	~Window();

	void Initialize(int width, int height, const char* title);
	void Update();
	void Destroy();

	bool ShouldClose();

	int GetWidth() { return width; }
	int GetHeight() { return height; }
	void createCallBacks();
	bool* GetKeys() { return keys; }
	GLfloat GetXChange();
	GLfloat GetYChange();
	bool GetMouseFirstMoved() { return mouseFirstMoved; }
	void SetMouseFirstMoved(bool mouseFirstMoved) { this->mouseFirstMoved = mouseFirstMoved; }
	bool GetIsMouseDisabled() { return isMouseDisabled; }
	void SetIsMouseDisabled(bool isMouseDisabled) { this->isMouseDisabled = isMouseDisabled; }
	GLFWwindow* GetWindow() { return window; }

private:
	GLFWwindow* window;
	int width, height;
	const char* title;
	bool keys[1024];

	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;

	bool mouseFirstMoved;
	bool isMouseDisabled;



	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);
};

