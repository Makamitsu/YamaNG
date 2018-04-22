#pragma once
#include "glm\glm.hpp"

#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

class Mesh {
private:
	VertexArray m_VAO;
	VertexBuffer m_VBO;
	IndexBuffer m_IBO;

	const void* m_VBdata;
	const unsigned int* m_IBdata;

public:
	Mesh(const void* VBdata, unsigned int VBsize, const unsigned int* IBdata, unsigned int IBsize);
	Mesh(const void* VBdata, unsigned int VBsize, const unsigned int* IBdata, unsigned int IBsize, const VertexBufferLayout& layout);
	~Mesh();

	unsigned int getCount() const { return m_IBO.getCount(); }
	void bind() const;

private:
	Mesh(const Mesh&) = delete;
};
