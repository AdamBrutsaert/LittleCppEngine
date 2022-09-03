#pragma once

#include <glm/glm.hpp>

namespace Genesis
{
	struct Vertex {
		glm::vec2 Position;

		union {
			glm::vec3 Color;
			glm::vec3 Texture;
		};
	};
}