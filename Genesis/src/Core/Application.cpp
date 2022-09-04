#include "Core/Application.h"

#include <chrono>
#include <stdexcept>

#include "Renderer/Renderer.h"
#include "MessageBus/MessageBus.h"

namespace Genesis
{
	static Application* s_Instance = nullptr;

	Application::Application(uint32_t width, uint32_t height, std::string const& title)
		: m_Width(width),
		  m_Height(height),
		  m_Title(title),
		  m_Window(nullptr),
		  m_Scene(nullptr),
		  m_NextScene(nullptr)
	{
		if (s_Instance != nullptr) {
			throw std::runtime_error("You can only create one Application!");
		}

		s_Instance = this;
	}

	std::shared_ptr<Window> const& Application::GetWindow()
	{
		return s_Instance->m_Window;
	}

	void Application::SetScene(std::shared_ptr<Scene> const& scene)
	{
		s_Instance->m_NextScene = scene;
	}

	void Application::run()
	{
		m_Window = std::make_shared<Window>(m_Width, m_Height, m_Title);

		Renderer::Initialize();

		if (m_NextScene == nullptr) {
			throw std::runtime_error("You must provide a Scene!");
		}

		m_Scene = m_NextScene;
		m_NextScene = nullptr;
		m_Scene->onAttach();

		auto begin = std::chrono::high_resolution_clock::now();
		decltype(begin) end;
		float dt;

		Renderer::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });

		while (!m_Window->shouldClose())
		{
			end = std::chrono::high_resolution_clock::now();
			dt = std::chrono::duration<float>(end - begin).count();
			begin = end;

			if (m_NextScene != nullptr) {
				m_Scene->onDetach();
				m_Scene = m_NextScene;
				m_NextScene = nullptr;
				m_Scene->onAttach();
			}

			MessageBus::Dispatch();

			Renderer::Clear();
			m_Scene->onUpdate(dt);

			m_Window->swapBuffers();
			Window::PollEvents();
		}

		m_Scene->onDetach();

		Renderer::Shutdown();
	}
}
