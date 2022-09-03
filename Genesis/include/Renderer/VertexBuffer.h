#pragma once

#include <memory>

#include <glad/glad.h>

#include "Vertex.h"

namespace Genesis
{
	class VertexBuffer
	{
	public:
		static std::shared_ptr<VertexBuffer> Create(uint32_t vertexCount, GLenum type);

		static void Unbind();

	public:
		VertexBuffer(uint32_t vertexCount, GLenum type);
		~VertexBuffer();

		void setData(Vertex* vertices, uint32_t count, uint32_t offset = 0);

		void bind() const;

	private:
		uint32_t m_BufferID;
	};
}