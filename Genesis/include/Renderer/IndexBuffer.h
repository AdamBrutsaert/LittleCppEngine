#pragma once

#include <glad/glad.h>
#include <cstdint>

namespace Genesis
{
	class IndexBuffer
	{
	public:
		IndexBuffer(uint32_t indexCount, GLenum type);
		~IndexBuffer();

		void setData(uint32_t* indices, uint32_t count, uint32_t offset = 0);

		void bind() const;
		static void Unbind();

	private:
		uint32_t m_BufferID;
	};
}