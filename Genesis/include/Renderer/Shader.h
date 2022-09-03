#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Genesis
{
	class Shader {
	public:
		Shader(const char* vertexSource, const char* fragmentSource);
		~Shader();

		Shader(const Shader&) = delete;
		Shader(Shader&&) = delete;
		Shader& operator=(const Shader&) = delete;

		void bind() const;
		static void Unbind();

		void setUniform1iv(char const* name, uint32_t count, int32_t* values);
		void setUniformMat4fv(char const* name, const glm::mat4& matrix);

	private:
		uint32_t m_ProgramID;
	};
}
