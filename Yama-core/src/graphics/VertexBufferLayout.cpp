#include "VertexBufferLayout.h"

#include <algorithm>

constexpr VertexBufferElement VertexBufferLayout::POSITION = { GL_FLOAT, 3, GL_FALSE, sizeof(float), VertexData::POSITION };
constexpr VertexBufferElement VertexBufferLayout::NORMAL = { GL_FLOAT, 3, GL_FALSE, sizeof(float), VertexData::NORMAL };
constexpr VertexBufferElement VertexBufferLayout::COLOR = { GL_FLOAT, 3, GL_FALSE, sizeof(float), VertexData::COLOR };
constexpr VertexBufferElement VertexBufferLayout::SPECULAR = { GL_FLOAT, 2, GL_FALSE, sizeof(float), VertexData::SPECULAR };
constexpr VertexBufferElement VertexBufferLayout::TEX_COORD = { GL_FLOAT, 2, GL_FALSE, sizeof(float), VertexData::TEX_COORD };
constexpr VertexBufferElement VertexBufferLayout::BONE_WEIGHT = { GL_FLOAT, 2, GL_FALSE, sizeof(float), VertexData::BONE_WEIGHT };

std::vector<VertexBufferElement>::const_iterator VertexBufferLayout::find(VertexData pData) {
	return std::find_if(m_Elements.begin(), m_Elements.end(), [&](VertexBufferElement vecTypeData) {return vecTypeData.dataType == pData; });
}

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
