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

	std::shared_ptr<VertexBuffer> VertexBuffer::Create(uint32_t vertexCount, GLenum type)
	{
		return std::make_shared<VertexBuffer>(vertexCount, type);
	}

	void VertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexBuffer::setData(Vertex* vertices, uint32_t count, uint32_t offset)
	{
		glBufferSubData(GL_ARRAY_BUFFER, offset * sizeof(Vertex), count * sizeof(Vertex), vertices);
	}

	void VertexBuffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	}
}