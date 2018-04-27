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
#include "graphics\Camera.h"

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"

#include "tools\Tools.h"


int main() {

	Window window("YamaEngine", 800, 600);
	glfwSetInputMode(window.mWindow, GLFW_STICKY_KEYS, 1);


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
	Model model(path);

	Texture texture("res/tex/piou.png");
	texture.bind();

	//shader.setUniform1i("u_Texture", 0);
	
	//glm::mat4 proj = glm::ortho(-50.0f, 50.0f, -25.0f, 25.5f, -100.0f, 100.0f);
	
	Renderer renderer;

	Mesh* sapin = model.getMeshes()[0];
	Mesh* trunk = model.getMeshes()[1];

	float posX = 10.0f;
	float posZ = 10.0f;

	Camera camera(glm::vec3(posX, 0.0f, posZ));
	camera.initProjection( 60.0f, 4.0f / 3.0f, 0.1f, 100.0f);

	glm::vec3 target(0.0f, 0.0f, 0.0f);
	camera.target = &target;
	
	glm::mat4 modele = glm::mat4( 1.0f );

	float test = 0.0f;
	float test2 = 0.0f;
	
	std::cout << "Load OK\n";
	while (!window.closed() ) {

		glm::vec3 deplacement(0.0f, 0.0f, 0.0f);
		if (glfwGetKey(window.mWindow, GLFW_KEY_UP) == GLFW_PRESS) ++(deplacement[2]);
		if (glfwGetKey(window.mWindow, GLFW_KEY_DOWN) == GLFW_PRESS) --deplacement[2];
		if (glfwGetKey(window.mWindow, GLFW_KEY_LEFT) == GLFW_PRESS) ++deplacement[0];
		if (glfwGetKey(window.mWindow, GLFW_KEY_RIGHT) == GLFW_PRESS) --deplacement[0];
		camera.move(deplacement);

		if (glfwGetKey(window.mWindow, GLFW_KEY_W) == GLFW_PRESS) camera.pitch -= 10.0f;
		if (glfwGetKey(window.mWindow, GLFW_KEY_S) == GLFW_PRESS) camera.pitch += 10.0f;
		if (glfwGetKey(window.mWindow, GLFW_KEY_A) == GLFW_PRESS) camera.yaw -= 10.0f;
		if (glfwGetKey(window.mWindow, GLFW_KEY_D) == GLFW_PRESS) camera.yaw += 10.0f;

		renderer.clear();

		glm::mat4 modele(1.0f);
		modele = glm::translate(modele, glm::vec3(0.0f, 0.0f, 0.0f));

		glm::vec3 offset;

		shader.setUniformMat4f( "u_MVP", camera.getProjection() * camera.getView() * modele  );

		renderer.clear();

		renderer.draw(*model.getMeshes()[0], shader);
		renderer.draw(*model.getMeshes()[1], shader);

		window.update();
	}
}