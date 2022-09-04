#pragma once

#include <glm/glm.hpp>

#include "Texture.h"

namespace Genesis
{
	class Renderer
	{
	public:
		static void Initialize();
		static void Shutdown();

		static void Begin();
		static void Begin(glm::mat4 const& ProjectionViewMatrix);
		static void End();

		static void SetClearColor(glm::vec4 color);
		static void Clear();

		// Colorized
		static void DrawTriangle(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, glm::vec3 color);
		static void DrawQuad(glm::vec2 position, glm::vec2 size, glm::vec3 color);
		static void DrawCircle(glm::vec2 position, float radius, glm::vec3 color, uint32_t precision = 50u);

		// Texturized
		static void DrawQuad(glm::vec2 position, glm::vec2 size, std::shared_ptr<Texture> const& texture, glm::vec4 subrect = { 0.0f, 0.0f, 1.0f, 1.0f });

		// Statistics
		struct Statistics {
			uint32_t DrawCalls = 0;

			uint32_t Vertices = 0;
			uint32_t Indices = 0;

			uint32_t Triangles = 0;
			uint32_t Quads = 0;
			uint32_t Circles = 0;
		};

		static Statistics GetStatistics();
		static void ResetStatistics();
	};
}