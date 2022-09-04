#pragma once

#include <glm/glm.hpp>

namespace Genesis
{
	class OrthographicCamera {
	public:
		OrthographicCamera(float aspectRatio);

		glm::mat4 getProjectionView() const;

		void setAspectRatio(float aspectRatio);
		void setZoomLevel(float level);
		void move(glm::vec2 offset);

	private:
		float m_AspectRatio;
		float m_ZoomLevel;
		glm::vec2 m_Position;

		glm::mat4 m_Projection;
		glm::mat4 m_View;
	};
}