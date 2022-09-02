#include <Genesis.h>

#include <iostream>

using namespace Genesis;

class SandboxScene : public Scene
{
public:
	SandboxScene() : m_Ticks(0), m_Elapsed(0) {}

	virtual void onAttach() override
	{
	}

	virtual void onDetach() override
	{
	}

	virtual void onUpdate(float dt) override
	{
		m_Ticks++;
		m_Elapsed += dt;

		if (m_Elapsed >= 1.0f) {
			Application::Get()->getWindow().setTitle("Ticks : " + std::to_string(m_Ticks));
			m_Ticks = 0;
			m_Elapsed -= 1.0f;
		}

		Renderer::Begin();
		Renderer::DrawQuad({ -0.5f, -0.5f }, { 1.0f, 1.0f }, { 0.92f, 0.53f, 1.0f });
		Renderer::DrawCircle({ 0.5f, 0.5f }, 0.25f, { 1.0f, 0.92f, 0.53f });
		Renderer::End();
	}

private:
	float m_Elapsed;
	uint32_t m_Ticks;
};

class Sandbox : public Application
{
public:
	Sandbox() : Application(1280, 720, "Ticks : Unknown") {
		setScene(std::make_shared<SandboxScene>());
	}
};

Application* CreateApplication()
{
	return new Sandbox();
}