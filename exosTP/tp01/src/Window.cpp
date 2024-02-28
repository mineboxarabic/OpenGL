#include "Window.h"

Window::Window()
{
	width = 800;
	height = 600;
	title = "OpenGL";
	for(int i = 0; i < 1024; i++)
		keys[i] = false;
	isMouseDisabled = false;
	mouseFirstMoved = true;
	
}

Window::Window(int width, int height, const char* title)
{
	this->width = width;
	this->height = height;
	this->title = title;

	for (int i = 0; i < 1024; i++)
		keys[i] = false;
	isMouseDisabled = false;
	mouseFirstMoved = true;

}




Window::~Window()
{
	Destroy();
}

void Window::Initialize(int width, int height, const char* title)
{	// ça part de là !


	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	this->width = width;
	this->height = height;
	this->title = title;

	if (!glfwInit())
	{
		std::cout << "GLFW failed to initialize" << std::endl;
		glfwTerminate();
	}


	window = glfwCreateWindow(width, height, title, NULL, NULL);

	if (!window)
	{
		std::cout << "GLFW failed to create window" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "GLAD failed to initialize" << std::endl;
		glfwTerminate();
	}

	glViewport(0, 0, width, height);

	//Set the pointer to this class so we can access it in the callbacks
	//Because the callbacks are static we can't access the class members
	//So we set the pointer to this class as the user pointer
	//Then we can access the class members in the callbacks
	glfwSetWindowUserPointer(window, this);
	createCallBacks();
}

void Window::createCallBacks() {
	glfwSetKeyCallback(window, handleKeys);
	glfwSetCursorPosCallback(window, handleMouse);
}

GLfloat Window::GetXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::GetYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}

void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode) {

	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		//set the mouse cursor to disabled
		theWindow->isMouseDisabled = !theWindow->isMouseDisabled;
		 glfwSetInputMode(window, GLFW_CURSOR, !theWindow->isMouseDisabled ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
	}

	if (theWindow->isMouseDisabled)
	{
		//Empty the keys array
		for (int i = 0; i < 1024; i++)
		{
			theWindow->keys[i] = false;
		}
		return;
	}
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) {
			theWindow->keys[key] = true;
			std::cout << "Pressed: " << key << std::endl;
		}
		else if (action == GLFW_RELEASE) {
			theWindow->keys[key] = false;
			std::cout << "Released: " << key << std::endl;
		}
	}


}
void Window::handleMouse(GLFWwindow* window,double xPos, double yPos)
{
	Window *theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	if (theWindow->isMouseDisabled)
	{
		
		return;
	}
	if (theWindow->mouseFirstMoved) {
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

		theWindow->xChange = xPos - theWindow->lastX;
		theWindow->yChange = theWindow->lastY - yPos;

		theWindow->lastX = xPos;
		theWindow->lastY = yPos;

		std::cout << "x: " << theWindow->xChange << " y: " << theWindow->yChange << std::endl;
}
void Window::Update()
{
	glfwSwapBuffers(window);
	glfwPollEvents();

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::Destroy()
{
	//glfwDestroyWindow(window);
	glfwTerminate();
}

bool Window::ShouldClose()
{
	return glfwWindowShouldClose(window);
}
