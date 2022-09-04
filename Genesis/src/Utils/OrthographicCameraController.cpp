#include "Utils/OrthographicCameraController.h"

#include "Core/Application.h"

namespace Genesis
{
	OrthographicCameraController::OrthographicCameraController()
		: m_Camera(1.0f)
	{
	}

	void OrthographicCameraController::onAttach()
	{
		m_Camera.setAspectRatio(
			static_cast<float>(Application::GetWindow()->getWidth()) /
			static_cast<float>(Application::GetWindow()->getHeight())
		);

		m_WindowResizeCallback = MessageBus::Subscribe<Message::WindowResize>(
			0,
			[this](Message::WindowResize m) {
				m_Camera.setAspectRatio(static_cast<float>(m.width) / static_cast<float>(m.height));
			}
		);
	}

	void OrthographicCameraController::onDetach()
	{
		MessageBus::Remove(0, m_WindowResizeCallback);
	}

	OrthographicCamera const& OrthographicCameraController::getCamera()
	{
		return m_Camera;
	}
}