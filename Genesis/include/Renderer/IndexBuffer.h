#pragma once

#include <cstdint>

#include <memory>

#include <glad/glad.h>

namespace Genesis
{
	class IndexBuffer
	{
	public:
		static std::shared_ptr<IndexBuffer> Create(uint32_t count, GLenum type);

		static void Unbind();

	public:
		IndexBuffer(uint32_t indexCount, GLenum type);
		~IndexBuffer();

		void setData(uint32_t* indices, uint32_t count, uint32_t offset = 0);

		void bind() const;

	private:
		uint32_t m_BufferID;
	};
}