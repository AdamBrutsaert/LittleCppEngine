#include "Precompiled.h"
#include "Renderer/Shader.h"

namespace Genesis
{
	static uint32_t CompileShader(std::string const& source, GLenum type)
	{
		char const* content = source.c_str();

		uint32_t shader = glCreateShader(type);
		glShaderSource(shader, 1, &content, nullptr);
		glCompileShader(shader);

		int success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			int size;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &size);

			std::vector<char> msg(size);
			glGetShaderInfoLog(shader, size, nullptr, msg.data());

			std::cerr << msg.data() << std::endl;
			throw std::runtime_error("Failed to compile Shader!");
		}

		return shader;
	}

	Shader::Shader(std::string const& vertexSource, std::string const& fragmentSource)
	{
		// Shaders
		auto vertex = CompileShader(vertexSource, GL_VERTEX_SHADER);
		auto fragment = CompileShader(fragmentSource, GL_FRAGMENT_SHADER);

		m_ProgramID = glCreateProgram();

		glAttachShader(m_ProgramID, vertex);
		glAttachShader(m_ProgramID, fragment);

		glLinkProgram(m_ProgramID);

		int success;
		glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &success);
		if (!success) {
			int size;
			glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &size);

			std::vector<char> msg(size);
			glGetProgramInfoLog(m_ProgramID, size, nullptr, msg.data());

			std::cerr << msg.data() << std::endl;
			throw std::runtime_error("Failed to link Shader!");
		}

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_ProgramID);
	}

	std::shared_ptr<Shader> Shader::CreateFromSources(std::string const& vertexSource, std::string const& fragmentSource)
	{
		return std::make_shared<Shader>(vertexSource, fragmentSource);
	}

	void Shader::Unbind()
	{
		glUseProgram(0);
	}

	void Shader::bind() const
	{
		glUseProgram(m_ProgramID);
	}

	void Shader::setUniform1iv(const char* name, uint32_t count, int32_t* values)
	{
		auto location = glGetUniformLocation(m_ProgramID, name);
		glUniform1iv(location, 16, values);
	}

	void Shader::setUniformMat4fv(char const* name, const glm::mat4& matrix)
	{
		auto location = glGetUniformLocation(m_ProgramID, name);
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}
