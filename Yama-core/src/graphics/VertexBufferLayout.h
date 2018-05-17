#pragma once

#include <vector>

#include "Renderer.h"

enum class VertexData {
	POSITION,
	NORMAL,
	SPECULAR,
	COLOR,
	TEX_COORD,
	BONE_WEIGHT
};

struct VertexBufferElement {
	unsigned int type;
	unsigned int count;
	unsigned char normalize;
	unsigned int typeSize;
	VertexData dataType;
};


class VertexBufferLayout {

private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;

public:
	VertexBufferLayout():m_Stride(0) {}

	template<unsigned int TypeEnum, unsigned int TypeSize>
	void push(unsigned int count, const VertexData& dataType);
	void push(VertexBufferElement data);

	VertexBufferLayout& operator[](const VertexBufferElement& data);

	inline const std::vector<VertexBufferElement>& getElements() const { return m_Elements; };
	inline unsigned int getStride() const { return m_Stride; };
	
	std::vector<VertexBufferElement>::const_iterator find(VertexData pData);

	static const VertexBufferElement POSITION;
	static const VertexBufferElement NORMAL;
	static const VertexBufferElement COLOR;
	static const VertexBufferElement SPECULAR;
	static const VertexBufferElement TEX_COORD;
	static const VertexBufferElement BONE_WEIGHT;
};
using DataType = VertexBufferLayout;

