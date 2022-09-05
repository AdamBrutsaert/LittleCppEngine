#include "Precompiled.h"
#include "Renderer/IndexBuffer.h"

#include "Core/Logger.h"

namespace Genesis
{
	IndexBuffer::IndexBuffer(uint32_t indexCount, GLenum type)
	{
		glGenBuffers(1, &m_BufferID);
		bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(uint32_t), nullptr, type);
		Unbind();
		LOG_INFO("Created Index Buffer.");
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_BufferID);
		LOG_INFO("Destroyed Index Buffer.");
	}

	std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t count, GLenum type)
	{
		return std::make_shared<IndexBuffer>(count, type);
	}

	void IndexBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void IndexBuffer::setData(uint32_t* indices, uint32_t count, uint32_t offset)
	{
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset * sizeof(uint32_t), count * sizeof(uint32_t), indices);
	}

	void IndexBuffer::bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
	}
}
