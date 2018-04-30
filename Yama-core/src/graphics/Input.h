#pragma once

#include "glm\glm.hpp"

struct GLFWwindow;

enum class Key {
	SPACE = 32,
	A = 65, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
	RIGHT = 262, LEFT, DOWN, UP,
	ESCAPE = 256, ENTER,
};
enum class Mouse {
	LEFT = 0, RIGHT, MIDDLE, BT4, BT5,
};

class Input {

	GLFWwindow* mWindow;
	double mDeltaMouseX;
	double mDeltaMouseY;
	double mLastMouseX;
	double mLastMouseY;


public:
	Input(GLFWwindow* mWindow);

	glm::vec2 getMouseDelta();

	void updateMouse();

	template<typename T>
	void keyPressed(Key pKey, T&& funct);

	template<typename T>
	void mousePressed(Mouse pKey, T&& funct);
};

template<typename T>
inline void Input::keyPressed(Key pKey, T && funct)
{
	if (glfwGetKey(mWindow, (int)pKey) == GLFW_PRESS) funct();
}

template<typename T>
inline void Input::mousePressed(Mouse pKey, T && funct)
{
	if (glfwGetMouseButton(mWindow, (int)pKey) == GLFW_PRESS) funct();
}
