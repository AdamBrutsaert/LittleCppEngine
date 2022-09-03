#include "Renderer/VertexArray.h"

namespace Genesis
{
	VertexArray::VertexArray(VertexBuffer const& vertexBuffer, IndexBuffer const& indexBuffer)
	{
		glGenVertexArrays(1, &m_VertexArrayID);
		bind();
			vertexBuffer.bind();
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, Position)));

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, Color)));

			indexBuffer.bind();
		Unbind();

		VertexBuffer::Unbind();
		IndexBuffer::Unbind();
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_VertexArrayID);
	}

	void VertexArray::bind() const
	{
		glBindVertexArray(m_VertexArrayID);
	}

	void VertexArray::Unbind()
	{
		glBindVertexArray(0);
	}
}