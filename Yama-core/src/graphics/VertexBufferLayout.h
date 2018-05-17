#pragma once

#include <vector>
#include <map>

#include "Renderer.h"

enum class VertexData {
	POSITION,
	NORMAL,
	SPECULAR,
	TEX_COORD,
	BONES_ID,
	BONES_WEIGHT,
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
	VertexBufferLayout() :m_Stride(0) {}

	template<unsigned int TypeEnum, unsigned int TypeSize>
	void push(unsigned int count, const VertexData& dataType);
	void push(VertexBufferElement data);

	VertexBufferLayout& operator[](const VertexBufferElement& data);

	inline const std::vector<VertexBufferElement>& getElements() const { return m_Elements; };
	inline unsigned int getStride() const { return m_Stride; };
	
	static const VertexBufferElement POSITION;
	static const VertexBufferElement NORMAL;
	static const VertexBufferElement SPECULAR;
	static const VertexBufferElement TEX_COORD;
	static const VertexBufferElement BONES_ID;
	static const VertexBufferElement BONES_WEIGHT;
};
using DataType = VertexBufferLayout;

