#include "SimpleGui.h"

#include "window.h"


SimpleGui::SimpleGui(GLFWwindow * pWindow):mWindow(pWindow)
{
	init();
}

SimpleGui::SimpleGui(const Window & window)
{
	mWindow = window.mWindow;
	init();
}

SimpleGui::~SimpleGui()
{
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
}

void SimpleGui::beginDraw()
{
	ImGui_ImplGlfwGL3_NewFrame();
}

void SimpleGui::draw()
{
	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}


void SimpleGui::init()
{
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(mWindow, true);
	ImGui::StyleColorsDark();
}