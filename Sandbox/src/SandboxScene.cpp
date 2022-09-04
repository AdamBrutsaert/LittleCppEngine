#include "SandboxScene.h"

#include <iostream>

using namespace Genesis;

SandboxScene::SandboxScene() : m_Ticks(0), m_Elapsed(0), m_Texture(nullptr) 
{
}

void SandboxScene::onAttach()
{
	m_Texture = new Texture("res/conveyor_0.png");
	m_Subscriber = MessageBus::Subscribe<Message::WindowResize>(
		0, 
		[](Message::WindowResize& m) { 
			std::cout << "Window Resized : (" << m.width << ", " << m.height << ")" << std::endl;
		}
	);

	m_Subscriber1 = MessageBus::Subscribe<Message::KeyPressed>(
		0,
		[](Message::KeyPressed& m) {
			std::cout << "Key " << m.key << " pressed!" << std::endl;
		}
	);

	m_Subscriber2 = MessageBus::Subscribe<Message::KeyReleased>(
		0,
		[](Message::KeyReleased& m) {
			std::cout << "Key " << m.key << " released!" << std::endl;
		}
	);
	
}

void SandboxScene::onDetach()
{
	delete m_Texture;
	MessageBus::Remove(0, m_Subscriber);
}

void SandboxScene::onUpdate(float dt)
{
	m_Ticks++;
	m_Elapsed += dt;

	if (m_Elapsed >= 1.0f) {
		Application::GetWindow()->setTitle("Ticks : " + std::to_string(m_Ticks));
		m_Ticks = 0;
		m_Elapsed -= 1.0f;
	}

	Renderer::ResetStatistics();

	Renderer::Begin();
	Renderer::DrawQuad({ -0.5f, -0.5f }, { 1.0f, 1.0f }, *m_Texture);
	Renderer::DrawCircle({ 0.5f, 0.5f }, 0.5f, { 1.0f, 0.92f, 0.53f });
	Renderer::End();
}
