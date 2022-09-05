#include "SandboxScene.h"
#include "SandboxLayer.h"

using namespace Genesis;

SandboxScene::SandboxScene() : m_Ticks(0), m_Elapsed(0)
{
}

void SandboxScene::onAttach()
{
	push(std::make_shared<SandboxLayer>());
}

void SandboxScene::onDetach()
{
	pop();
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
}
