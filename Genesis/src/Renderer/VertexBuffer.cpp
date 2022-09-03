#include "Renderer/VertexBuffer.h"

namespace Genesis
{
	VertexBuffer::VertexBuffer(uint32_t vertexCount, GLenum type)
	{
		glGenBuffers(1, &m_BufferID);
		bind();
		glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), nullptr, type);
		Unbind();
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_BufferID);
	}

	void VertexBuffer::setData(Vertex* vertices, uint32_t count, uint32_t offset)
	{
		glBufferSubData(GL_ARRAY_BUFFER, offset * sizeof(Vertex), count * sizeof(Vertex), vertices);
	}

	void VertexBuffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	}

	void VertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}