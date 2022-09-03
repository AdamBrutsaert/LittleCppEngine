#include "Renderer/VertexArray.h"

namespace Genesis
{
	VertexArray::VertexArray(std::shared_ptr<VertexBuffer> const& vertexBuffer,
							 std::shared_ptr<IndexBuffer> const& indexBuffer)
	{
		glGenVertexArrays(1, &m_VertexArrayID);
		bind();
			vertexBuffer->bind();
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, Position)));

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, Color)));

			indexBuffer->bind();
		Unbind();

		VertexBuffer::Unbind();
		IndexBuffer::Unbind();
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_VertexArrayID);
	}

	std::shared_ptr<VertexArray> VertexArray::Create(std::shared_ptr<VertexBuffer> const& vertexBuffer, std::shared_ptr<IndexBuffer> const& indexBuffer)
	{
		return std::make_shared<VertexArray>(vertexBuffer, indexBuffer);
	}

	void VertexArray::Unbind()
	{
		glBindVertexArray(0);
	}
	
	void VertexArray::bind() const
	{
		glBindVertexArray(m_VertexArrayID);
	}
}