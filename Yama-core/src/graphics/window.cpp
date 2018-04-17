#include "window.h"

#include <GLFW\glfw3.h>
#include <iostream>

namespace yama {
	namespace graphics {


		void windowResizeCallback(GLFWwindow* window, int width, int height);

		Window::Window(const char* pTitle, int pWidth, int pHeight)
			:mTitle(pTitle), mWidth(pWidth), mHeight(pHeight)
		{
			init();
		}

		void Window::update()
		{
			glfwSwapBuffers(mWindow);
			glfwGetFramebufferSize(mWindow, &mWidth, &mHeight );
			glfwPollEvents();
		}

		Window::~Window()
		{
			glfwDestroyWindow(mWindow);
			glfwTerminate();
		}

		void Window::clear()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
			glfwSetWindowSizeCallback(mWindow, windowResizeCallback);
			return true;
		}

		void windowResizeCallback(GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}
	}
}
