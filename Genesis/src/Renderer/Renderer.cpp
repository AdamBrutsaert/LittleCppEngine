#include "Precompiled.h"
#include "Renderer/Renderer.h"

#include "Core/Logger.h"
#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"
#include "MessageBus/MessageBus.h"

namespace Genesis
{
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
		switch (int(fColor.z) - 2) {
		case 0:
			Color = texture(uTextures[0], fColor.xy);
			break;
		case 1:
			Color = texture(uTextures[1], fColor.xy);
			break;
		case 2:
			Color = texture(uTextures[2], fColor.xy);
			break;
		case 3:
			Color = texture(uTextures[3], fColor.xy);
			break;
		case 4:
			Color = texture(uTextures[4], fColor.xy);
			break;
		case 5:
			Color = texture(uTextures[5], fColor.xy);
			break;
		case 6:
			Color = texture(uTextures[6], fColor.xy);
			break;
		case 7:
			Color = texture(uTextures[7], fColor.xy);
			break;
		case 8:
			Color = texture(uTextures[8], fColor.xy);
			break;
		case 9:
			Color = texture(uTextures[9], fColor.xy);
			break;
		case 10:
			Color = texture(uTextures[10], fColor.xy);
			break;
		case 11:
			Color = texture(uTextures[11], fColor.xy);
			break;
		case 12:
			Color = texture(uTextures[12], fColor.xy);
			break;
		case 13:
			Color = texture(uTextures[13], fColor.xy);
			break;
		case 14:
			Color = texture(uTextures[14], fColor.xy);
			break;
		default:
			Color = texture(uTextures[15], fColor.xy);
			break;
		}
	}
	else 
	{
		Color = vec4(fColor, 1.0);
	}
}
)";

	static constexpr uint32_t MAX_VERTICES = 50'000;
	static constexpr uint32_t MAX_INDICES = 200'000;
	static constexpr uint32_t MAX_TEXTURES = 16; // OpenGL3 ensures that there is at least 16 textures availables

	static std::shared_ptr<Shader> s_Shader = nullptr;
	static std::shared_ptr<VertexBuffer> s_VertexBuffer = nullptr;
	static std::shared_ptr<IndexBuffer> s_IndexBuffer = nullptr;
	static std::shared_ptr<VertexArray> s_VertexArray = nullptr;

	static glm::mat4 s_ProjectionViewMatrix{ 1.0f };

	// Maybe batch Vertices and Indices together into a single array
	static Vertex* s_Vertices = nullptr;
	static uint32_t* s_Indices = nullptr;
	static std::array<std::shared_ptr<Texture>, MAX_TEXTURES> s_Textures = { nullptr };

	static uint32_t s_VertexCount = 0;
	static uint32_t s_IndexCount = 0;
	static uint32_t s_TextureCount = 0;
	
	// Statistics
	static Renderer::Statistics s_Statistics;

	void Renderer::Initialize()
	{
		MessageBus::Subscribe<Message::WindowResize>(
			0,
			[](Message::WindowResize m) { 
				glViewport(0, 0, m.width, m.height);
			}
		);

		s_Shader = Shader::CreateFromSources(s_VertexSource, s_FragmentSource);
	
		// Preparing textures
		{
			int32_t samplers[16];
			for (auto i = 0; i < 16; i++) samplers[i] = i;
			
			s_Shader->bind();
			s_Shader->setUniform1iv("uTextures", 16, samplers);
			Shader::Unbind();
		}

		s_Vertices = new Vertex[MAX_VERTICES];
		s_Indices = new uint32_t[MAX_INDICES];

		s_VertexBuffer = VertexBuffer::Create(MAX_VERTICES, GL_DYNAMIC_DRAW);
		s_IndexBuffer = IndexBuffer::Create(MAX_INDICES, GL_DYNAMIC_DRAW);
		s_VertexArray = VertexArray::Create(s_VertexBuffer, s_IndexBuffer);

		LOG_INFO("Initialized Renderer.");
	}

	void Renderer::Shutdown()
	{
		s_Shader = nullptr;
		s_VertexBuffer = nullptr;
		s_IndexBuffer = nullptr;
		s_VertexArray = nullptr;
		s_Textures = { nullptr };

		delete[] s_Vertices;
		delete[] s_Indices;
		
		LOG_INFO("Shutdowned Renderer.");
	}

	void Renderer::Begin()
	{
		s_VertexCount = 0;
		s_IndexCount = 0;
		s_TextureCount = 0;
	}

	void Renderer::Begin(glm::mat4 const& ProjectionViewMatrix)
	{
		s_ProjectionViewMatrix = ProjectionViewMatrix;
		Renderer::Begin();
	}

	void Renderer::End()
	{
		s_Shader->bind();

			s_Shader->setUniformMat4fv("uViewProjection", s_ProjectionViewMatrix);

			s_VertexArray->bind();
				
				s_VertexBuffer->bind();
				s_VertexBuffer->setData(s_Vertices, s_VertexCount);

				s_IndexBuffer->bind();
				s_IndexBuffer->setData(s_Indices, s_IndexCount);

				for (uint32_t i = 0; i < s_TextureCount; i++) {
					s_Textures[i]->bind(i);
				}

				glDrawElements(GL_TRIANGLES, s_IndexCount, GL_UNSIGNED_INT, nullptr);

			VertexArray::Unbind();

			VertexBuffer::Unbind();
			IndexBuffer::Unbind();

		Shader::Unbind();

		s_Statistics.DrawCalls += 1;
	}

	void Renderer::SetClearColor(glm::vec4 color)
	{
		glClearColor(color.x, color.y, color.z, color.w);
	}

	void Renderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::DrawTriangle(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, glm::vec3 color) {
		// Check if there are enough space
		if (s_VertexCount + 3 > MAX_VERTICES || s_IndexCount + 3 > MAX_INDICES)
		{
			Renderer::End();
			Renderer::Begin();
		}

		// Vertices
		s_Vertices[s_VertexCount].Position = p1;
		s_Vertices[s_VertexCount].Color = color;

		s_Vertices[s_VertexCount + 1].Position = p2;
		s_Vertices[s_VertexCount + 1].Color = color;

		s_Vertices[s_VertexCount + 2].Position = p3;
		s_Vertices[s_VertexCount + 2].Color = color;

		// Indices
		s_Indices[s_IndexCount] = s_VertexCount;
		s_Indices[s_IndexCount + 1] = s_VertexCount + 1;
		s_Indices[s_IndexCount + 2] = s_VertexCount + 2;

		s_VertexCount += 3;
		s_IndexCount += 3;

		s_Statistics.Vertices += 3;
		s_Statistics.Indices += 3;
		s_Statistics.Triangles += 1;
	}

	void Renderer::DrawQuad(glm::vec2 position, glm::vec2 size, glm::vec3 color)
	{
		// Check if there are enough space
		if (s_VertexCount + 4 > MAX_VERTICES || s_IndexCount + 6 > MAX_INDICES)
		{
			Renderer::End();
			Renderer::Begin();
		}

		// Vertices
		s_Vertices[s_VertexCount].Position = position;
		s_Vertices[s_VertexCount].Color = color;

		s_Vertices[s_VertexCount + 1].Position = position + glm::vec2{ size.x, 0.0f };
		s_Vertices[s_VertexCount + 1].Color = color;

		s_Vertices[s_VertexCount + 2].Position = position + glm::vec2{ size.x, size.y };
		s_Vertices[s_VertexCount + 2].Color = color;

		s_Vertices[s_VertexCount + 3].Position = position + glm::vec2{ 0.0f, size.y };
		s_Vertices[s_VertexCount + 3].Color = color;

		// Indices
		s_Indices[s_IndexCount] = s_VertexCount;
		s_Indices[s_IndexCount + 1] = s_VertexCount + 1;
		s_Indices[s_IndexCount + 2] = s_VertexCount + 2;
		s_Indices[s_IndexCount + 3] = s_VertexCount + 2;
		s_Indices[s_IndexCount + 4] = s_VertexCount + 3;
		s_Indices[s_IndexCount + 5] = s_VertexCount;

		s_VertexCount += 4;
		s_IndexCount += 6;

		s_Statistics.Vertices += 4;
		s_Statistics.Indices += 6;
		s_Statistics.Quads += 1;
	}

	void Renderer::DrawCircle(glm::vec2 position, float radius, glm::vec3 color, uint32_t precision) {
		// Constants
		constexpr float PI = 3.14159265358979323846f;

		// Check if there are enough space
		if (s_VertexCount + precision + 1 > MAX_VERTICES || s_IndexCount + 3 * precision > MAX_INDICES) {
			Renderer::End();
			Renderer::Begin();
		}

		// Vertices
		s_Vertices[s_VertexCount].Position = position;
		s_Vertices[s_VertexCount].Color = color;

		for (uint32_t i = 1; i <= precision; i++) {
			s_Vertices[s_VertexCount + i].Position = {
				position.x + radius * std::cos(2 * PI / precision * (i - 1)),
				position.y + radius * std::sin(2 * PI / precision * (i - 1)),
			};
			s_Vertices[s_VertexCount + i].Color = color;
		}

		// Indices
		for (uint32_t i = 0; i < precision - 1; i++) {
			s_Indices[s_IndexCount + i * 3] = s_VertexCount;
			s_Indices[s_IndexCount + i * 3 + 1] = s_VertexCount + i + 1;
			s_Indices[s_IndexCount + i * 3 + 2] = s_VertexCount + i + 2;
		}

		s_Indices[s_IndexCount + (precision - 1) * 3] = s_VertexCount;
		s_Indices[s_IndexCount + (precision - 1) * 3 + 1] = s_VertexCount + precision;
		s_Indices[s_IndexCount + (precision - 1) * 3 + 2] = s_VertexCount + 1;

		s_VertexCount += 1 + precision;
		s_IndexCount += 3 * precision;

		s_Statistics.Vertices += 1 + precision;
		s_Statistics.Indices += 3 * precision;
		s_Statistics.Circles += 1;
	}

	void Renderer::DrawQuad(glm::vec2 position, glm::vec2 size, std::shared_ptr<Texture> const& texture, glm::vec4 subrect)
	{
		// Check if there are enough space
		if (s_VertexCount + 4 > MAX_VERTICES || s_IndexCount + 6 > MAX_INDICES)
		{
			Renderer::End();
			Renderer::Begin();
		}

		// Find texture
		float textureID = -1.0f;
		for (uint32_t i = 0; i < s_TextureCount; i++)
		{
			if (s_Textures[i] == texture)
				textureID = i;
		}

		if (textureID == -1.0f)
		{
			// Check if there is enough place for the texture
			if (s_TextureCount + 1 > MAX_TEXTURES)
			{
				Renderer::End();
				Renderer::Begin();
			}

			s_Textures[s_TextureCount] = texture;
			textureID = s_TextureCount;
			s_TextureCount++;
		}


		// Vertices
		s_Vertices[s_VertexCount].Position = position;
		s_Vertices[s_VertexCount].Texture = { subrect.x, subrect.y, textureID + 2.0f };

		s_Vertices[s_VertexCount + 1].Position = position + glm::vec2{ size.x, 0.0f };
		s_Vertices[s_VertexCount + 1].Texture = { subrect.x + subrect.z, subrect.y, textureID + 2.0f };

		s_Vertices[s_VertexCount + 2].Position = position + glm::vec2{ size.x, size.y };
		s_Vertices[s_VertexCount + 2].Texture = { subrect.x + subrect.z, subrect.y + subrect.w, textureID + 2.0f };

		s_Vertices[s_VertexCount + 3].Position = position + glm::vec2{ 0.0f, size.y };
		s_Vertices[s_VertexCount + 3].Texture = { subrect.x, subrect.y + subrect.w, textureID + 2.0f };

		// Indices
		s_Indices[s_IndexCount] = s_VertexCount;
		s_Indices[s_IndexCount + 1] = s_VertexCount + 1;
		s_Indices[s_IndexCount + 2] = s_VertexCount + 2;
		s_Indices[s_IndexCount + 3] = s_VertexCount + 2;
		s_Indices[s_IndexCount + 4] = s_VertexCount + 3;
		s_Indices[s_IndexCount + 5] = s_VertexCount;

		s_VertexCount += 4;
		s_IndexCount += 6;

		s_Statistics.Vertices += 4;
		s_Statistics.Indices += 6;
		s_Statistics.Quads += 1;
	}

	Renderer::Statistics Renderer::GetStatistics() {
		return s_Statistics;
	}

	void Renderer::ResetStatistics() {
		s_Statistics = Statistics{};
	}
}
