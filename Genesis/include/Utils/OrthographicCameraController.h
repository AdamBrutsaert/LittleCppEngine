#pragma once

#include "OrthographicCamera.h"
#include "MessageBus/MessageBus.h"

namespace Genesis
{
	class OrthographicCameraController {
	public:
		OrthographicCameraController();

		void onAttach();
		void onDetach();
		void onUpdate(float dt);

		OrthographicCamera const& getCamera();

	private:
		OrthographicCamera m_Camera;

		MessageSubscriber<Message::WindowResize> m_WindowResizeCallback;
		MessageSubscriber<Message::MouseScroll> m_MouseScrollCallback;
	};
}
