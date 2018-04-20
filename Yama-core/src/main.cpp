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

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"


int main() {

	using namespace yama::graphics;

	Window window("YamaEngine", 800, 600);

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));



	auto simpleMan = aiImportFile("res/models/simpleMan2.blend", aiProcessPreset_TargetRealtime_MaxQuality);

	std::cout << "Meches found: " << simpleMan->mNumMeshes << "\n";
	std::cout << "Vertices found: " << simpleMan->mMeshes[0]->mNumVertices << "\n" ;

	auto vertices = simpleMan->mMeshes[0]->mVertices;

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


	VertexArray va;
	VertexBuffer vb(vertices, simpleMan->mMeshes[0]->mNumVertices * 3 * sizeof(float));

	VertexBufferLayout layout;
	layout.push<GL_FLOAT, sizeof(GLfloat)>(3);
	//layout.push<GL_FLOAT, sizeof(GLfloat)>(2);
	va.addBuffer(vb, layout);

	IndexBuffer vi(indices, 6 * sizeof(unsigned int));



	glm::mat4 proj = glm::ortho(-200.0f, 200.0f, -100.5f, 100.5f, -100.0f, 100.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, 0.0f));

	glm::mat4 mvp =  proj * view;

	Shader shader("res/shaders/Basic.shader");
	shader.bind();

	Texture texture("res/tex/piou.png");
	texture.bind();
	shader.setUniform1i("u_Texture", 0);
	shader.setUniformMat4f("u_MVP", mvp);

	va.unbind();
	vi.unbind();
	vb.unbind();
	shader.unbind();

	Renderer renderer;

	float incr = 0.02;
	float val = 0.5;

	while (!window.closed() ) {

		renderer.clear();

		renderer.draw(va, vi, shader);
		
		window.update();
	}
}