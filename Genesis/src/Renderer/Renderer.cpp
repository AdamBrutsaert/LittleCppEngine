#include "Renderer/Renderer.h"

#include <memory>
#include <array>

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Renderer/Shader.h"

namespace Genesis
{
	struct Vertex {
		glm::vec2 Position;

		union {
			glm::vec3 Color;
			glm::vec3 Texture;
		};
	};

	static std::string s_VertexSource = R"(
#version 330 core

layout (location = 0) in vec2 vPosition;
layout (location = 1) in vec3 vColor;

out vec3 fColor;

uniform mat4 uViewProjection;

void main()
{
	gl_Position = uViewProjection * vec4(vPosition, 0.0, 1.0);
	fColor = vColor;
}
)";

	static std::string s_FragmentSource = R"(
#version 330 core

uniform sampler2D uTextures[16];

in vec3 fColor;

out vec4 Color;

void main()
{
	if (fColor.z > 1.0)
	{
		Color = texture(uTextures[int(fColor.z) - 2], fColor.xy);
	}
	else 
	{
		Color = vec4(fColor, 1.0);
	}
}
)";

	static std::unique_ptr<Shader> s_Shader;

	static constexpr uint32_t MAX_VERTICES = 50'000;
	static constexpr uint32_t MAX_INDICES = 200'000;
	static constexpr uint32_t MAX_TEXTURES = 16; // OpenGL3 ensures that there is at least 16 textures availables

	static uint32_t VertexArray = 0;
	static uint32_t VertexBuffer = 0;
	static uint32_t IndexBuffer = 0;

	// Maybe batch Vertices and Indices together into a single array
	static Vertex* Vertices = nullptr;
	static uint32_t* Indices = nullptr;
	static std::array<uint32_t, MAX_TEXTURES> Textures;

	static uint32_t VertexCount = 0;
	static uint32_t IndexCount = 0;
	static uint32_t TextureCount = 0;
	
	// Statistics
	Renderer::Statistics Stats;

	void Renderer::Initialize()
	{
		s_Shader = std::make_unique<Shader>(s_VertexSource, s_FragmentSource);
	
		// Preparing textures
		{
			int samplers[16];
			for (auto i = 0; i < 16; i++) samplers[i] = i;
			
			s_Shader->bind();
			s_Shader->setUniform1iv("uTextures", 16, samplers);
			Shader::Unbind();
		}

		Vertices = new Vertex[MAX_VERTICES];
		Indices = new uint32_t[MAX_INDICES];

		glGenVertexArrays(1, &VertexArray);
		glBindVertexArray(VertexArray);

			glGenBuffers(1, &VertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, MAX_VERTICES * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, Position)));

				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, Color)));

			glGenBuffers(1, &IndexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, MAX_INDICES * sizeof(uint32_t), nullptr, GL_DYNAMIC_DRAW);

		glBindVertexArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void Renderer::Shutdown()
	{
		glDeleteBuffers(1, &IndexBuffer);
		glDeleteBuffers(1, &VertexBuffer);
		glDeleteVertexArrays(1, &VertexArray);

		delete[] Vertices;
		delete[] Indices;
	}

	void Renderer::Begin()
	{
		VertexCount = 0;
		IndexCount = 0;
		TextureCount = 0;
	}

	void Renderer::End()
	{
		s_Shader->bind();

			s_Shader->setUniformMat4fv("uViewProjection", glm::ortho(-16.0f / 9.0f, 16.0f / 9.0f, -1.0f, 1.0f));

			glBindVertexArray(VertexArray);

				// Vertex Buffer
				glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
				glBufferSubData(GL_ARRAY_BUFFER, 0, VertexCount * sizeof(Vertex), Vertices);

				// Index Buffer
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
				glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, IndexCount * sizeof(uint32_t), Indices);

				// Textures
				for (uint32_t i = 0; i < TextureCount; i++) {
					glActiveTexture(GL_TEXTURE0 + i);
					glBindTexture(GL_TEXTURE_2D, Textures[i]);
				}

				glDrawElements(GL_TRIANGLES, IndexCount, GL_UNSIGNED_INT, nullptr);

			glBindVertexArray(0);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		Shader::Unbind();

		Stats.DrawCalls += 1;
	}

	void Renderer::DrawTriangle(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, glm::vec3 color) {
		// Check if there are enough space
		if (VertexCount + 3 > MAX_VERTICES || IndexCount + 3 > MAX_INDICES)
		{
			Renderer::End();
			Renderer::Begin();
		}

		// Vertices
		Vertices[VertexCount].Position = p1;
		Vertices[VertexCount].Color = color;

		Vertices[VertexCount + 1].Position = p2;
		Vertices[VertexCount + 1].Color = color;

		Vertices[VertexCount + 2].Position = p3;
		Vertices[VertexCount + 2].Color = color;

		// Indices
		Indices[IndexCount] = VertexCount;
		Indices[IndexCount + 1] = VertexCount + 1;
		Indices[IndexCount + 2] = VertexCount + 2;

		VertexCount += 3;
		IndexCount += 3;

		Stats.Vertices += 3;
		Stats.Indices += 3;
		Stats.Triangles += 1;
	}

	void Renderer::DrawQuad(glm::vec2 position, glm::vec2 size, glm::vec3 color)
	{
		// Check if there are enough space
		if (VertexCount + 4 > MAX_VERTICES || IndexCount + 6 > MAX_INDICES)
		{
			Renderer::End();
			Renderer::Begin();
		}

		// Vertices
		Vertices[VertexCount].Position = position;
		Vertices[VertexCount].Color = color;

		Vertices[VertexCount + 1].Position = position + glm::vec2{ size.x, 0.0f };
		Vertices[VertexCount + 1].Color = color;

		Vertices[VertexCount + 2].Position = position + glm::vec2{ size.x, size.y };
		Vertices[VertexCount + 2].Color = color;

		Vertices[VertexCount + 3].Position = position + glm::vec2{ 0.0f, size.y };
		Vertices[VertexCount + 3].Color = color;

		// Indices
		Indices[IndexCount] = VertexCount;
		Indices[IndexCount + 1] = VertexCount + 1;
		Indices[IndexCount + 2] = VertexCount + 2;
		Indices[IndexCount + 3] = VertexCount + 2;
		Indices[IndexCount + 4] = VertexCount + 3;
		Indices[IndexCount + 5] = VertexCount;

		VertexCount += 4;
		IndexCount += 6;

		Stats.Vertices += 4;
		Stats.Indices += 6;
		Stats.Quads += 1;
	}

	void Renderer::DrawCircle(glm::vec2 position, float radius, glm::vec3 color, uint32_t precision) {
		// Constants
		constexpr float PI = 3.14159265358979323846f;

		// Check if there are enough space
		if (VertexCount + precision + 1 > MAX_VERTICES || IndexCount + 3 * precision > MAX_INDICES) {
			Renderer::End();
			Renderer::Begin();
		}

		// Vertices
		Vertices[VertexCount].Position = position;
		Vertices[VertexCount].Color = color;

		for (uint32_t i = 1; i <= precision; i++) {
			Vertices[VertexCount + i].Position = {
				position.x + radius * std::cos(2 * PI / precision * (i - 1)),
				position.y + radius * std::sin(2 * PI / precision * (i - 1)),
			};
			Vertices[VertexCount + i].Color = color;
		}

		// Indices
		for (uint32_t i = 0; i < precision - 1; i++) {
			Indices[IndexCount + i * 3] = VertexCount;
			Indices[IndexCount + i * 3 + 1] = VertexCount + i + 1;
			Indices[IndexCount + i * 3 + 2] = VertexCount + i + 2;
		}

		Indices[IndexCount + (precision - 1) * 3] = VertexCount;
		Indices[IndexCount + (precision - 1) * 3 + 1] = VertexCount + precision;
		Indices[IndexCount + (precision - 1) * 3 + 2] = VertexCount + 1;

		VertexCount += 1 + precision;
		IndexCount += 3 * precision;

		Stats.Vertices += 1 + precision;
		Stats.Indices += 3 * precision;
		Stats.Circles += 1;
	}

	void Renderer::DrawQuad(glm::vec2 position, glm::vec2 size, uint32_t texture, glm::vec4 subrect)
	{
		// Check if there are enough space
		if (VertexCount + 4 > MAX_VERTICES || IndexCount + 6 > MAX_INDICES)
		{
			Renderer::End();
			Renderer::Begin();
		}

		// Find texture
		float textureID = -1.0f;
		for (uint32_t i = 0; i < TextureCount; i++)
		{
			if (Textures[i] == texture)
				textureID = i;
		}

		if (textureID == -1.0f)
		{
			// Check if there is enough place for the texture
			if (TextureCount + 1 > MAX_TEXTURES)
			{
				Renderer::End();
				Renderer::Begin();
			}

			Textures[TextureCount] = texture;
			textureID = TextureCount;
			TextureCount++;
		}


		// Vertices
		Vertices[VertexCount].Position = position;
		Vertices[VertexCount].Texture = { subrect.x, subrect.y, textureID + 2.0f };

		Vertices[VertexCount + 1].Position = position + glm::vec2{ size.x, 0.0f };
		Vertices[VertexCount + 1].Texture = { subrect.x + subrect.z, subrect.y, textureID + 2.0f };

		Vertices[VertexCount + 2].Position = position + glm::vec2{ size.x, size.y };
		Vertices[VertexCount + 2].Texture = { subrect.x + subrect.z, subrect.y + subrect.w, textureID + 2.0f };

		Vertices[VertexCount + 3].Position = position + glm::vec2{ 0.0f, size.y };
		Vertices[VertexCount + 3].Texture = { subrect.x, subrect.y + subrect.w, textureID + 2.0f };

		// Indices
		Indices[IndexCount] = VertexCount;
		Indices[IndexCount + 1] = VertexCount + 1;
		Indices[IndexCount + 2] = VertexCount + 2;
		Indices[IndexCount + 3] = VertexCount + 2;
		Indices[IndexCount + 4] = VertexCount + 3;
		Indices[IndexCount + 5] = VertexCount;

		VertexCount += 4;
		IndexCount += 6;

		Stats.Vertices += 4;
		Stats.Indices += 6;
		Stats.Quads += 1;
	}

	Renderer::Statistics Renderer::GetStatistics() {
		return Stats;
	}

	void Renderer::ResetStatistics() {
		Stats = Statistics{};
	}
}