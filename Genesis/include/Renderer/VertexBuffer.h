#pragma once

#include <glad/glad.h>

#include "Vertex.h"

namespace Genesis
{
	class VertexBuffer
	{
	public:
		VertexBuffer(uint32_t vertexCount, GLenum type);
		~VertexBuffer();

		void setData(Vertex* vertices, uint32_t count, uint32_t offset = 0);

		void bind() const;
		static void Unbind();

	private:
		uint32_t m_BufferID;
	};
}