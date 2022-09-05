#include "Precompiled.h"
#include "Utils/OrthographicCameraController.h"

#include "Core/Application.h"
#include "Core/Input.h"

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

		m_MouseScrollCallback = MessageBus::Subscribe<Message::MouseScroll>(
			0,
			[this](Message::MouseScroll m) {
				if (m.y != 0 && m_Camera.getZoomLevel() >= 0.1f) {
					m_Camera.setZoomLevel(
						std::clamp(m_Camera.getZoomLevel() / std::pow(1.1, m.y), 0.1, 100.0)
					);
				}
			}			
		);
	}

	void OrthographicCameraController::onDetach()
	{
		MessageBus::Remove(0, m_WindowResizeCallback);
	}

	void OrthographicCameraController::onUpdate(float dt)
	{
		glm::ivec2 direction = { 0, 0 };

		if (Input::IsKeyPressed(Key::Z)) direction.y += 1;
		if (Input::IsKeyPressed(Key::S)) direction.y -= 1;
		if (Input::IsKeyPressed(Key::Q)) direction.x -= 1;
		if (Input::IsKeyPressed(Key::D)) direction.x += 1;

		if (direction != glm::ivec2{ 0, 0 }) {
			m_Camera.move({ direction.x * dt, direction.y * dt });
		}
	}

	OrthographicCamera const& OrthographicCameraController::getCamera()
	{
		return m_Camera;
	}
}
