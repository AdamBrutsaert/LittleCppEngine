#pragma once

#include <memory>

#include "EntryPoint.h"
#include "Window.h"
#include "Scene.h"

namespace Genesis
{
	class Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void setScene(std::shared_ptr<Scene> scene);

		static Application* Get();

	private:
		void run();

	private:
		friend int ::main();

		Window m_Window;
		std::shared_ptr<Scene> m_Scene;
		std::shared_ptr<Scene> m_NextScene;
	};
}