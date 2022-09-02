#include "Core/Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

namespace Genesis 
{
	static bool s_IsGLFWInitialized = false;
	static bool s_IsGLADInitialized = false;
	static uint32_t s_WindowCount = 0;

	static void InitializeGLFW()
	{
		if (!s_IsGLFWInitialized) {
			if (!glfwInit()) {
				throw std::runtime_error("Failed to initialize GLFW!");
			}
			s_IsGLFWInitialized = true;
		}
	}

	static void ShutdownGLFW()
	{
		if (s_WindowCount == 0 && s_IsGLFWInitialized) {
			glfwTerminate();
			s_IsGLFWInitialized = false;
		}
	}

	static void InitializeGLAD()
	{
		if (!s_IsGLADInitialized) {
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
				throw std::runtime_error("Failed to initialize GLAD!");
			}
			s_IsGLADInitialized = true;
		}
	}

	Window::Window(uint32_t width, uint32_t height, std::string const& title)
	{
		InitializeGLFW();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

		if (m_Window == nullptr) {
			throw std::runtime_error("Failed to create Window!");
		}

		glfwMakeContextCurrent(static_cast<GLFWwindow*>(m_Window));
		InitializeGLAD();

		s_WindowCount++;
	}

	Window::~Window()
	{
		glfwDestroyWindow(static_cast<GLFWwindow*>(m_Window));
		s_WindowCount--;

		ShutdownGLFW();
	}

	bool Window::shouldClose() const
	{
		return glfwWindowShouldClose(static_cast<GLFWwindow*>(m_Window));
	}

	void Window::swapBuffers() const
	{
		glfwSwapBuffers(static_cast<GLFWwindow*>(m_Window));
	}

	void Window::PollEvents()
	{
		glfwPollEvents();
	}
}