#include "Input.h"

#include "GLFW\glfw3.h"


Input::Input(GLFWwindow * pWindow):mWindow(pWindow), mDeltaMouseX(0), mDeltaMouseY(0), mLastMouseX(0), mLastMouseY(0)
{
}

glm::vec2 Input::getMouseDelta()
{
	return glm::vec2((int)mDeltaMouseX, (int)mDeltaMouseY );
}

void Input::updateMouse() {
	double xpos, ypos;
	glfwGetCursorPos(mWindow, &xpos, &ypos);
	mDeltaMouseX = mLastMouseX - xpos;
	mDeltaMouseY = mLastMouseY - ypos;
	mLastMouseX = xpos;
	mLastMouseY = ypos;
}