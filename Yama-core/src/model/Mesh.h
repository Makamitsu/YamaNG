#pragma once
#include "glm\glm.hpp"

#include "..\graphics\Shader.h"
#include "..\graphics\VertexArray.h"
#include "..\graphics\VertexBuffer.h"
#include "..\graphics\IndexBuffer.h"
#include "..\graphics\VertexBufferLayout.h"
#include "Texture.h"
#include "Material.h"

class Texture;
class Material;
class VertexBufferLayout;
class IndexBuffer;
class VertexBuffer;
class VertexArray;
class Shader;

class Mesh {
private:
	VertexArray m_VAO;
	VertexBuffer m_VBO;
	IndexBuffer m_IBO;
	Material* m_MaterialIndex;

	const void* m_VBdata;
	const unsigned int* m_IBdata;

public:
	Mesh(const void* VBdata, unsigned int VBsize, const unsigned int* IBdata, unsigned int IBsize);
	Mesh(const void* VBdata, unsigned int VBsize, const unsigned int* IBdata, unsigned int IBsize, const VertexBufferLayout& layout);
	~Mesh();

	unsigned int getCount() const { return m_IBO.getCount(); }
	void bind() const;

	void setMaterial(Material* materialIndex);

private:
	Mesh(const Mesh&) = delete;
};
