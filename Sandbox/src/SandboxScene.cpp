#include "SandboxScene.h"

#include <iostream>

using namespace Genesis;

SandboxScene::SandboxScene() : m_Ticks(0), m_Elapsed(0), m_Texture(nullptr) 
{
}

void SandboxScene::onAttach()
{
	m_Texture = new Texture("res/conveyor_0.png");
}

void SandboxScene::onDetach()
{
	delete m_Texture;
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

	auto stats = Renderer::GetStatistics();

	std::cout << "Draw Calls : " << stats.DrawCalls << "\r";
}
