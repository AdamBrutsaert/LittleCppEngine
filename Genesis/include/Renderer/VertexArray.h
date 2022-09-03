#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Genesis
{
	class VertexArray
	{
	public:
		static std::shared_ptr<VertexArray> Create(std::shared_ptr<VertexBuffer> const& vertexBuffer,
												   std::shared_ptr<IndexBuffer> const& indexBuffer);

		static void Unbind();

	public:
		VertexArray(std::shared_ptr<VertexBuffer> const& vertexBuffer,
					std::shared_ptr<IndexBuffer> const& indexBuffer);
		~VertexArray();

		void bind() const;

	private:
		uint32_t m_VertexArrayID;
	};
}