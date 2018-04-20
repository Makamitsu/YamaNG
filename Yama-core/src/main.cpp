#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <iostream>

#include "graphics\window.h"
#include "graphics\Renderer.h"
#include "graphics\VertexBuffer.h"
#include "graphics\IndexBuffer.h"
#include "graphics\VertexArray.h"
#include "graphics\VertexBufferLayout.h"
#include "graphics\Shader.h"

int main() {

	using namespace yama::graphics;

	Window window("YamaEngine", 800, 600);

	GLCall(glClearColor(0.2f,0.2f,1.0f,1.0f));

	float positions[] = {
		-0.5f, 0.5f,
		0.5f, 0.5f,
		0.5f, -0.5f,
		-0.5f, -0.5f
	};
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	VertexArray va;
	VertexBuffer vb(positions, 8 * sizeof(float));

	VertexBufferLayout layout;
	layout.push<GL_FLOAT, sizeof(GLfloat)>(2);
	va.addBuffer(vb, layout);

	IndexBuffer vi(indices, 6*sizeof(unsigned int));

	Shader shader("res/shaders/Basic.shader");
	shader.bind();
	shader.setUniform4f("u_Color", 0.6, 0.0, 0.4, 1.0);
	shader.unbind();

	Renderer renderer;

	float incr = 0.02;
	float val = 0.5;

	while (!window.closed() ) {

		renderer.clear();

		if (val > 1) incr = -0.02;
		else if (val < 0) incr = 0.02;
		val += incr;
		shader.setUniform4f("u_Color", 1.0 - val, val, 0.3, 1.0);

		renderer.draw(va, vi, shader);
		
		window.update();
	}

}