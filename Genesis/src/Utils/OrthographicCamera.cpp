#include "Utils/OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Genesis
{
	OrthographicCamera::OrthographicCamera(float aspectRatio)
		: m_AspectRatio(aspectRatio),
		  m_ZoomLevel(1.0f),
		  m_Position(0.0f, 0.0f),
		  m_View(glm::translate(glm::mat4(1.0f), glm::vec3(-m_Position.x, -m_Position.y, 0.0f))),
		  m_Projection(glm::ortho(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel))
	{
	}

	glm::mat4 OrthographicCamera::getProjectionView() const
	{
		return m_Projection * m_View;
	}

	float OrthographicCamera::getZoomLevel() const
	{
		return m_ZoomLevel;
	}

	void OrthographicCamera::setAspectRatio(float aspectRatio)
	{
		m_AspectRatio = aspectRatio;
		m_Projection = glm::ortho(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}

	void OrthographicCamera::setZoomLevel(float level)
	{
		m_ZoomLevel = level;
		m_Projection = glm::ortho(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}

	void  OrthographicCamera::move(glm::vec2 offset)
	{
		m_Position += offset;
		m_View = glm::translate(glm::mat4(1.0f), glm::vec3(-m_Position.x, -m_Position.y, 0.0f));
	}
}
