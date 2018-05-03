#include "Renderer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "IndexBuffer.h"
#include "..\model\Mesh.h"
#include "..\model\Model.h"

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
	va.bind();
	ib.bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::draw(Mesh& mesh, Shader& shader) const
{
	shader.bind();
	mesh.bind();
	GLCall(glDrawElements(GL_TRIANGLES, mesh.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::draw(Model& model, Shader& Shader) const
{
	for (Mesh* mesh : model.getMeshes())
		draw(*mesh, Shader);
}
