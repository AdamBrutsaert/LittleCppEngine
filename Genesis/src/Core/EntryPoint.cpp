#include "Core/Application.h"

#include "Renderer/Renderer.h"

extern Genesis::Application* CreateApplication();

int main()
{
	auto app = CreateApplication();

	Genesis::Renderer::Initialize();
	app->run();
	Genesis::Renderer::Shutdown();
	
	delete app;
}
