#include "Mesh.h"


Mesh::Mesh(const void* VBdata, unsigned int VBsize, const unsigned int* IBdata, unsigned int IBsize):
	m_VAO(), m_VBO(VBdata, VBsize), m_IBO(IBdata, IBsize), m_VBdata(VBdata), m_IBdata(IBdata)
{
	VertexBufferLayout layout;
	layout[DataType::POSITION][DataType::NORMAL][DataType::TEX_COORD];
	m_VAO.addBuffer(m_VBO, layout);
}

Mesh::Mesh(const void* VBdata, unsigned int VBsize, const unsigned int* IBdata, unsigned int IBsize, const VertexBufferLayout& layout) :
	m_VAO(), m_VBO(VBdata, VBsize), m_IBO(IBdata, IBsize)
{
	m_VAO.addBuffer(m_VBO, layout);
}

Mesh::~Mesh()
{
	delete[] m_VBdata;
	delete[] m_IBdata;
}

void Mesh::bind() const
{
	m_VAO.bind();
	m_IBO.bind();
}

void Mesh::setMaterial(Material * materialIndex)
{
	m_MaterialIndex = materialIndex;
}
