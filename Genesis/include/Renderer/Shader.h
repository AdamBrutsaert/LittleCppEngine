#pragma once

#include <string>
#include <memory>

#include <glm/glm.hpp>

namespace Genesis
{
	class Shader {
	public:
		static std::shared_ptr<Shader> CreateFromSources(std::string const& vertexSource, std::string const& fragmentSource);

		static void Unbind();
		
	public:
		Shader(std::string const& vertexSource, std::string const& fragmentSource);
		~Shader();

		Shader(const Shader&) = delete;
		Shader(Shader&&) = delete;
		Shader& operator=(const Shader&) = delete;

		void bind() const;

		void setUniform1iv(char const* name, uint32_t count, int32_t* values);
		void setUniformMat4fv(char const* name, const glm::mat4& matrix);

	private:
		uint32_t m_ProgramID;
	};
}
