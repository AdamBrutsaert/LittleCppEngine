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
		Application(uint32_t width, uint32_t height, std::string const& title);
		virtual ~Application() = default;

		static std::shared_ptr<Window> const& GetWindow();
		static void SetScene(std::shared_ptr<Scene> const& scene);

	private:
		void run();

	private:
		friend int ::main();

		uint32_t m_Width;
		uint32_t m_Height;
		std::string m_Title;

		std::shared_ptr<Window> m_Window;

		std::shared_ptr<Scene> m_Scene;
		std::shared_ptr<Scene> m_NextScene;
	};
}
