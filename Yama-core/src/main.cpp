#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <iostream>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "graphics\window.h"
#include "graphics\Renderer.h"
#include "graphics\VertexBuffer.h"
#include "graphics\IndexBuffer.h"
#include "graphics\VertexArray.h"
#include "graphics\VertexBufferLayout.h"
#include "graphics\Shader.h"
#include "graphics\Texture.h"
#include "graphics\Mesh.h"
#include "graphics\Model.h"

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"

#include "tools\Tools.h"
#define TIMER(x); Utils::Timer t(#x);x;t.printElapsed();

float posX, posZ= 0;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		posZ += 1.0f;
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
		posZ -= 1.0f;
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
		posX += 1.0f;
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
		posX -= 1.0f;
}



int main() {

	Window window("YamaEngine", 800, 600);
	glfwSetKeyCallback(window.mWindow, key_callback);


	float positions[] = {
		-0.5f, 0.5f,  0.0, 1.0,
		 0.5f, 0.5f,  1.0, 1.0,
		 0.5f,-0.5f,  1.0, 0.0,
		-0.5f,-0.5f,  0.0, 0.0,
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	VertexBufferLayout layout;
	layout.push<GL_FLOAT, 4>(2, VertexBufferElementType::POSITION);
	layout.push<GL_FLOAT, 4>(2, VertexBufferElementType::TEX_COORD);
	Mesh mesh(positions, 4 * 4 * sizeof(float), indices, 6 * sizeof(unsigned int), layout);

	Shader shader("res/shaders/Basic.shader");
	shader.bind();

	std::string path = "res/models/simpleLowPolyEnv.blend";
	TIMER(Model model(path));

	Texture texture("res/tex/piou.png");
	texture.bind();
	//shader.setUniform1i("u_Texture", 0);
	
	//glm::mat4 proj = glm::ortho(-50.0f, 50.0f, -25.0f, 25.5f, -100.0f, 100.0f);
	
	Renderer renderer;


	float test = 0;
	while (!window.closed() ) {
		test += 0.1;
		glm::mat4 proj = glm::perspective(glm::radians(test),4.0f / test, 0.1f , 100.0f );
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(posX, 0.0f, posZ));
		glm::mat4 mvp = proj * view;
		shader.setUniformMat4f("u_MVP", mvp);

		renderer.clear();

		renderer.draw(model, shader);
		
		window.update();
	}
}