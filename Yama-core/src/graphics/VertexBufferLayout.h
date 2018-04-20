#pragma once

#include <vector>

#include "Renderer.h"

struct VertexBufferElement {
	unsigned int type;
	unsigned int count;
	unsigned char normalize;
	unsigned int typeSize;
};


class VertexBufferLayout {

private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;

public:
	VertexBufferLayout() :m_Stride(0) {}
	
	template<unsigned int TypeEnum, unsigned int TypeSize>
	void push(unsigned int count) {
		m_Elements.push_back({ TypeEnum, count, GL_FALSE, TypeSize });
		m_Stride += count * TypeSize;
	}

	inline const std::vector<VertexBufferElement>& getElements() const { return m_Elements; };
	inline unsigned int getStride() const { return m_Stride; };


};