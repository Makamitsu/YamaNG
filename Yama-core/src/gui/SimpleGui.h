#pragma once

#include "imgui\imgui.h"
#include "imgui\imgui_impl_glfw_gl3.h"

#include "GLFW\glfw3.h"

class Window;

class SimpleGui {

private:
	GLFWwindow* mWindow;
public:
	SimpleGui(GLFWwindow* pWindow);
	SimpleGui(const Window& window);
	~SimpleGui();


	void beginDraw();

	void draw();
private:
	void init();


};