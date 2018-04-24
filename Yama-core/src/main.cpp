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

float posX= 0;
float posZ= -30;
bool keys[4] = { false };
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_W)
		if (action == GLFW_PRESS) keys[0] = true;
		if (action == GLFW_RELEASE) keys[0] = false;
	if (key == GLFW_KEY_S)
		if (action == GLFW_PRESS) keys[1] = true;
		if (action == GLFW_RELEASE) keys[1] = false;
	if (key == GLFW_KEY_A)
		if (action == GLFW_PRESS) keys[2] = true;
		if (action == GLFW_RELEASE) keys[2] = false;
	if (key == GLFW_KEY_D)
		if (action == GLFW_PRESS) keys[3] = true;
		if (action == GLFW_RELEASE) keys[3] = false;
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

	Mesh* sapin = model.getMeshes()[0];
	Mesh* trunk = model.getMeshes()[1];

	glm::mat4 proj = glm::mat4( 1.0f );
	glm::mat4 view = glm::mat4( 1.0f );
	glm::mat4 modele = glm::mat4( 1.0f );

	float test = 0.0f;
	float test2 = 0.0f;
	while (!window.closed() ) {
		renderer.clear();

		glm::mat4 proj = glm::perspective( glm::radians( 60.0f ), 4.0f / 3.0f, 0.1f, 100.0f );
		glm::mat4 view = glm::translate( glm::mat4(1.0f), glm::vec3( posX, 0.0f, posZ ) );
		glm::mat4 modele = glm::rotate( glm::mat4(1.0f), glm::radians( ++test ), glm::vec3( 0.0f, 1.0f, 0.0f ) );

		shader.setUniformMat4f( "u_MVP", proj * view * modele );

		if (keys[0]) ++posZ;
		if (keys[1]) --posZ;
		if (keys[2]) ++posX;
		if (keys[3]) --posX;

		//renderer.draw(*model.getMeshes()[18], shader);
		//renderer.draw(*model.getMeshes()[19], shader);
		//renderer.draw(*model.getMeshes()[20], shader);

		renderer.draw(*model.getMeshes()[21], shader);
		renderer.draw(*model.getMeshes()[22], shader);

		//renderer.draw(*model.getMeshes()[50], shader);
		//renderer.draw(*model.getMeshes()[51], shader);

		test2 = (test2) > 54.0f ? 0.0f: test2 += 0.01f;
		//renderer.draw(*model.getMeshes()[ (int)test2 ], shader);

		std::cout << (int)test2 << std::endl;

		window.update();
	}
}