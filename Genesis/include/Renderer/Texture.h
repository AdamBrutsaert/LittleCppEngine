#pragma once

#include <string>
#include <memory>

namespace Genesis
{
	class Texture
	{
	public:
		static std::shared_ptr<Texture> Create(std::string const& path);

		static void Unbind(uint32_t location);

	public:
		Texture(std::string const& path);
		~Texture();

		void bind(uint32_t location) const;

	private:
		uint32_t m_TextureID;
	};
}