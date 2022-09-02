#include <Genesis.h>

#include <iostream>

using namespace Genesis;

class SandboxScene : public Scene
{
public:
	SandboxScene(int32_t id) : m_Id(id), m_Elapsed(0) {}

	virtual void onAttach() override
	{
		std::cout << "Attach " << m_Id << std::endl;
	}

	virtual void onDetach() override
	{
		std::cout << "Detach " << m_Id << std::endl;

	}

	virtual void onUpdate(float dt) override
	{
		m_Elapsed += dt;

		if (m_Elapsed >= 2.0f) {
			Application::Get()->setScene(std::make_shared<SandboxScene>(m_Id + 1));
		}
	}

private:
	int32_t m_Id;
	float m_Elapsed;
};

class Sandbox : public Application
{
public:
	Sandbox() {
		setScene(std::make_shared<SandboxScene>(0));
	}
};

Application* CreateApplication()
{
	return new Sandbox();
}