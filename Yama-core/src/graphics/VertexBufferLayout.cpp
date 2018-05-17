#include "VertexBufferLayout.h"

constexpr VertexBufferElement VertexBufferLayout::POSITION = { GL_FLOAT, 3, GL_FALSE, sizeof(float), VertexData::POSITION };
constexpr VertexBufferElement VertexBufferLayout::NORMAL = { GL_FLOAT, 3, GL_FALSE, sizeof(float), VertexData::NORMAL };
constexpr VertexBufferElement VertexBufferLayout::SPECULAR = { GL_FLOAT, 2, GL_FALSE, sizeof(float), VertexData::SPECULAR };
constexpr VertexBufferElement VertexBufferLayout::TEX_COORD = { GL_FLOAT, 2, GL_FALSE, sizeof(float), VertexData::TEX_COORD };
constexpr VertexBufferElement VertexBufferLayout::BONES_ID = { GL_UNSIGNED_INT, 1, GL_FALSE, sizeof(unsigned int), VertexData::BONES_ID };
constexpr VertexBufferElement VertexBufferLayout::BONES_WEIGHT = { GL_FLOAT, 1, GL_FALSE, sizeof(float), VertexData::BONES_WEIGHT };

template<unsigned int TypeEnum, unsigned int TypeSize>
void VertexBufferLayout::push(unsigned int count, const VertexData& dataType) {
	m_Elements.push_back({ TypeEnum, count, GL_FALSE, TypeSize, dataType });
	m_Stride += count * TypeSize;
}

void VertexBufferLayout::push(VertexBufferElement data) {
	m_Elements.push_back(data);
	m_Stride += data.count * data.typeSize;
}

VertexBufferLayout& VertexBufferLayout::operator[](const VertexBufferElement& data) {
	push(data);
	return *this;
}
