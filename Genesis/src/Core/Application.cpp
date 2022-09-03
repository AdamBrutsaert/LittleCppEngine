#include "Core/Application.h"

#include <chrono>
#include <stdexcept>

#include <glad/glad.h>

namespace Genesis
{
	static Application* s_Instance = nullptr;

	Application::Application() 
		: m_Window(1280, 720, "Genesis Engine"),
		  m_Scene(nullptr), 
		  m_NextScene(nullptr)
	{
		s_Instance = this;
	}

	Application::Application(uint32_t width, uint32_t height, std::string const& title)
		: m_Window(width, height, title),
		  m_Scene(nullptr),
		  m_NextScene(nullptr)
	{
		s_Instance = this;
	}

	Window& Application::getWindow()
	{
		return m_Window;
	}

	void Application::setScene(std::shared_ptr<Scene> scene)
	{
		m_NextScene = scene;
	}

	Application* Application::Get()
	{
		return s_Instance;
	}

	void Application::run()
	{
		if (m_NextScene == nullptr) {
			throw std::runtime_error("You must provide a Scene!");
		}

		m_Scene = m_NextScene;
		m_NextScene = nullptr;
		m_Scene->onAttach();

		auto begin = std::chrono::high_resolution_clock::now();
		decltype(begin) end;
		float dt;

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

		while (!m_Window.shouldClose())
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

			glClear(GL_COLOR_BUFFER_BIT);

			m_Scene->onUpdate(dt);

			m_Window.swapBuffers();
			Window::PollEvents();
		}

		m_Scene->onDetach();
	}
}
