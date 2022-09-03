#pragma once

#include <string>

namespace Genesis
{
	class Texture
	{
	public:
		Texture(std::string const& path);
		~Texture();

		void bind(uint32_t location) const;
		static void Unbind(uint32_t location);

	private:
		uint32_t m_TextureID;
	};
}