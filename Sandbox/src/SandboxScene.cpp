#include "SandboxScene.h"

#include <iostream>

using namespace Genesis;

SandboxScene::SandboxScene() : m_Ticks(0), m_Elapsed(0), m_CameraController()
{
}

void SandboxScene::onAttach()
{
	m_CameraController.onAttach();
}

void SandboxScene::onDetach()
{
	m_CameraController.onDetach();
}

void SandboxScene::onUpdate(float dt)
{
	m_CameraController.onUpdate(dt);

	m_Ticks++;
	m_Elapsed += dt;

	if (m_Elapsed >= 1.0f) {
		Application::GetWindow()->setTitle("Ticks : " + std::to_string(m_Ticks));
		m_Ticks = 0;
		m_Elapsed -= 1.0f;
	}

	Renderer::ResetStatistics();

	Renderer::Begin(m_CameraController.getCamera().getProjectionView());
	Renderer::DrawCircle({ 0.5f, 0.5f }, 0.5f, { 1.0f, 0.92f, 0.53f });
	Renderer::End();
}
