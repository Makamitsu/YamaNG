#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <iostream>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "window\window.h"
#include "graphics\Renderer.h"
#include "graphics\VertexBuffer.h"
#include "graphics\IndexBuffer.h"
#include "graphics\VertexArray.h"
#include "graphics\VertexBufferLayout.h"
#include "graphics\Shader.h"
#include "model\Texture.h"
#include "model\Mesh.h"
#include "model\Model.h"
#include "graphics\Camera.h"
#include "input\Input.h"
#include "gui\SimpleGui.h"

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

	std::string path = "res/models/model1.fbx";
	Model model(path);

	Texture texture("res/tex/piou.png");
	texture.bind();
	//shader.setUniform1i("u_Texture", 0);
	
	Renderer renderer;

	Mesh* sapin = model.getMeshes()[0];

	float posX = 10.0f;
	float posZ = 10.0f;

	Camera camera(glm::vec3(posX, 0.0f, posZ));
	camera.initProjection( 60.0f, 4.0f / 3.0f, 0.1f, 100.0f);

	glm::vec3 target(0.0f, 0.0f, 0.0f);
	camera.target = &target;
	
	glm::mat4 modele = glm::mat4( 1.0f );

	float test = 0.0f;
	
	SimpleGui gui(window);

	std::cout << "Load OK\n";
	while (!window.closed() ) {

		gui.beginDraw();

		window.mInput->keyPressed(Key::W, [&](){camera.pitch -= 10.0f; });
		window.mInput->keyPressed(Key::S, [&](){camera.pitch += 10.0f; });
		window.mInput->keyPressed(Key::A, [&](){camera.yaw -= 10.0f; });
		window.mInput->keyPressed(Key::D, [&](){camera.yaw += 10.0f; });

		window.mInput->updateMouse();
		glm::vec2 mouseDisplacement = window.mInput->getMouseDelta();
		window.mInput->mousePressed(Mouse::LEFT, [&]() {
			camera.pitch += mouseDisplacement[1]/10;
			camera.yaw += mouseDisplacement[0]/10;
		});

		glm::vec3 deplacement(0.0f, 0.0f, 0.0f);
		window.mInput->keyPressed(Key::RIGHT, [&]() { ++(deplacement[0]); });
		window.mInput->keyPressed(Key::LEFT, [&]() { --(deplacement[0]); });
		window.mInput->keyPressed(Key::DOWN, [&]() { ++(deplacement[2]); });
		window.mInput->keyPressed(Key::UP, [&]() { --(deplacement[2]); });
		camera.move(deplacement);

		renderer.clear();

		glm::mat4 modele(1.0f);
		modele = glm::translate(modele, glm::vec3(0.0f, 0.0f, 0.0f));
		modele = glm::rotate(modele, glm::radians(++test), glm::vec3(0.0f, 1.0f, 0.0f));

		shader.setUniformMat4f( "u_MVP", camera.getProjection() * camera.getView() * modele  );

		renderer.clear();
		renderer.draw(*model.getMeshes()[0], shader);

		ImGui::Text("Chargement du model: ok!");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		gui.draw();
		window.update();
	}
}