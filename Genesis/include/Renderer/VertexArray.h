#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Genesis
{
	class VertexArray
	{
	public:
		VertexArray(VertexBuffer const& vertexBuffer, IndexBuffer const& indexBuffer);
		~VertexArray();

		void bind() const;
		static void Unbind();

	private:
		uint32_t m_VertexArrayID;
	};
}