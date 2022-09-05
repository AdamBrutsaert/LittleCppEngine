#include "SandboxLayer.h"

using namespace Genesis;

SandboxLayer::SandboxLayer() : m_CameraController(), m_TextureElapsed(0), m_TextureIndex(0)
{

}

void SandboxLayer::onAttach()
{
    m_CameraController.onAttach();
	m_Texture = Texture::Create("res/Conveyor Belt.png");
}

void SandboxLayer::onDetach()
{

}

void SandboxLayer::onUpdate(float dt)
{
    m_CameraController.onUpdate(dt);

    m_TextureElapsed += dt;
	if (m_TextureElapsed >= 0.1f) {
		m_TextureIndex = (m_TextureIndex + 1) % 8;
		m_TextureElapsed -= 0.1f;
	}

	Renderer::ResetStatistics();
	Renderer::Begin(m_CameraController.getCamera().getProjectionView());
	Renderer::DrawCircle({ 0.5f, 0.5f }, 0.5f, { 1.0f, 0.92f, 0.53f });
	Renderer::DrawQuad({ -0.5f, -0.5f}, { 1.0f, 1.0f }, m_Texture, { 0.125f * m_TextureIndex, 0.75f, 0.125f, 0.25f });
	Renderer::DrawQuad({ -0.5f, 0.5f}, { 1.0f, 1.0f }, m_Texture, { 0.125f * m_TextureIndex, 0.75f, 0.125f, 0.25f });
	Renderer::DrawQuad({ -0.5f, 1.5f}, { 1.0f, 1.0f }, m_Texture, { 0.125f * m_TextureIndex, 0.75f, 0.125f, 0.25f });
	Renderer::DrawQuad({ -0.5f, 2.5f}, { 1.0f, 1.0f }, m_Texture, { 0.125f * m_TextureIndex, 0.75f, 0.125f, 0.25f });
	Renderer::End();
}
