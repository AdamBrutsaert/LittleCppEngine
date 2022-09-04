#include "SandboxScene.h"

#include <iostream>

using namespace Genesis;

SandboxScene::SandboxScene() : m_Ticks(0), m_Elapsed(0), m_Texture(nullptr), m_CameraController()
{
}

void SandboxScene::onAttach()
{
	m_Texture = Texture::Create("res/conveyor_0.png");
	m_CameraController.onAttach();
}

void SandboxScene::onDetach()
{
	m_CameraController.onDetach();
	m_Texture = nullptr;
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

	Renderer::Begin(m_CameraController.getCamera().getProjectionView());
	Renderer::DrawQuad({ -0.5f, -0.5f }, { 1.0f, 1.0f }, m_Texture);
	Renderer::DrawCircle({ 0.5f, 0.5f }, 0.5f, { 1.0f, 0.92f, 0.53f });
	Renderer::End();
}
