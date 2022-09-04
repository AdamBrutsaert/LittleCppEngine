#include "SandboxScene.h"

#include <iostream>

using namespace Genesis;

SandboxScene::SandboxScene() : m_Ticks(0), m_Elapsed(0), m_Texture(nullptr) 
{
}

void SandboxScene::onAttach()
{
	m_Texture = new Texture("res/conveyor_0.png");
	m_Subscriber0 = MessageBus::Subscribe<MyMessage>(0, [](MyMessage& m) { std::cout << "[0] Received MyEvent : " << m.value << std::endl; MessageBus::PreventPropagation(); });
	m_Subscriber1 = MessageBus::Subscribe<MyMessage>(1, [](MyMessage& m) { std::cout << "[1] Received MyEvent : " << m.value << std::endl; });
}

void SandboxScene::onDetach()
{
	delete m_Texture;
	MessageBus::Remove(1, m_Subscriber1);
	MessageBus::Remove(0, m_Subscriber0);
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

	MessageBus::Send<MyMessage>(23u);
}
