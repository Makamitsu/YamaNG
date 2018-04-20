#include "Renderer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "IndexBuffer.h"

#include <iostream>


void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

void Renderer::clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

bool GLLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "[OPENGL Error] (" << error << "): " << function << " on " << file << ":" << line << "\n";
		return false;
	}
	return true;
}

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, Shader& shader) const
{
	shader.bind();
	//shader.setUniform4f("u_Color", 1.0, 0.0, 0.0, 1.0);
	va.bind();
	ib.bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));

}
