#include "SandboxScene.h"

class Sandbox : public Genesis::Application
{
public:
	Sandbox() : Genesis::Application(1280u, 720u, "Ticks : Unknown") {
		SetScene(std::make_shared<SandboxScene>());
	}
};

Genesis::Application* CreateApplication()
{
	return new Sandbox();
}
