#include "Precompiled.h"
#include "Core/Application.h"

extern Genesis::Application* CreateApplication();

int main()
{
	auto app = CreateApplication();
	app->run();
	delete app;
}
