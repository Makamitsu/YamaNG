#include "VertexArray.h"

#include "Renderer.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
	GLCall(glBindVertexArray(m_RendererID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	bind();
	vb.bind();
	const auto& elements = layout.getElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); ++i) {
		auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalize, layout.getStride(), (const void*)offset ));
		//GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (const void*)0 ));
		offset += element.count * element.typeSize;
	}
}

void VertexArray::bind() const{
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::unbind() const {
	GLCall(glBindVertexArray(0));
}

