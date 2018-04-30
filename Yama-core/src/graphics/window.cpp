#include <GL\glew.h>
#include "window.h"
#include "Renderer.h"
#include "Input.h"

#include <GLFW\glfw3.h>
#include <iostream>


void windowResizeCallback(GLFWwindow* window, int width, int height);

Window::Window(const char* pTitle, int pWidth, int pHeight)
	:mTitle(pTitle), mWidth(pWidth), mHeight(pHeight)
{
	init();
	GLCall(glClearColor(0.2f, 0.2f, 1.0f, 1.0f));
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glDepthFunc(GL_LESS));
}

void Window::update()
{
	glfwSwapBuffers(mWindow);
	glfwPollEvents();
}

Window::~Window()
{
	delete mInput;
	glfwDestroyWindow(mWindow);
	glfwTerminate();
}

bool Window::closed()
{
	return glfwWindowShouldClose(mWindow);
}

bool Window::init()
{
	if (!glfwInit()) {
		std::cout << "GLFW Window failed to init!\n";
		return false;
	}
	mWindow = glfwCreateWindow(mWidth, mHeight, mTitle, nullptr, nullptr);
	if (!mWindow) {
		std::cout << "GLFW Window failed to create the window!\n";
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(mWindow);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			
	glewInit();

	glfwSwapInterval(1);
	glfwSetWindowSizeCallback(mWindow, windowResizeCallback);

	mInput = new Input(this->mWindow);

	return true;
}

void windowResizeCallback(GLFWwindow* window, int width, int height)
{
	GLCall(glViewport(0, 0, width, height));
}
	

