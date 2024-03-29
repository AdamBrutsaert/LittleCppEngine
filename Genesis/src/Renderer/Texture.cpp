#include "Precompiled.h"
#include "Renderer/Texture.h"

#include "Core/Logger.h"

namespace Genesis
{
	Texture::Texture(std::string const& path)
		: m_TextureID(0)
	{
		int w, h, bits;

		stbi_set_flip_vertically_on_load(true);
		auto* pixels = stbi_load(path.c_str(), &w, &h, &bits, STBI_rgb);

		if (pixels == nullptr) LOG_ERROR("Failed to load texture \"{}\".", path);

		glGenTextures(1, &m_TextureID);

		glBindTexture(GL_TEXTURE_2D, m_TextureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);

		stbi_image_free(pixels);

		LOG_INFO("Created Texture.");
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_TextureID);
		LOG_INFO("Destroyed Texture.");
	}

	std::shared_ptr<Texture> Texture::Create(std::string const& path)
	{
		return std::make_shared<Texture>(path);
	}

	void Texture::Unbind(uint32_t location)
	{
		glActiveTexture(GL_TEXTURE0 + location);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
	void Texture::bind(uint32_t location) const
	{
		glActiveTexture(GL_TEXTURE0 + location);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
	}
}
