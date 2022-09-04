#include "Core/Window.h"

#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "MessageBus/MessageBus.h"
#include "Core/Key.h"

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

	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		MessageBus::Send<Message::WindowResize>(static_cast<uint32_t>(width), static_cast<uint32_t>(height));
	}

	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Key trueKey = Key::UNKNOWN;
		switch (key)
		{
		case 81:
			trueKey = Key::A;
			break;
		case 66:
			trueKey = Key::B;
			break;
		case 67:
			trueKey = Key::C;
			break;
		case 68:
			trueKey = Key::D;
			break;
		case 69:
			trueKey = Key::E;
			break;
		case 70:
			trueKey = Key::F;
			break;
		case 71:
			trueKey = Key::G;
			break;
		case 72:
			trueKey = Key::H;
			break;
		case 73:
			trueKey = Key::I;
			break;
		case 74:
			trueKey = Key::J;
			break;
		case 75:
			trueKey = Key::K;
			break;
		case 76:
			trueKey = Key::L;
			break;
		case 59:
			trueKey = Key::M;
			break;
		case 78:
			trueKey = Key::N;
			break;
		case 79:
			trueKey = Key::O;
			break;
		case 80:
			trueKey = Key::P;
			break;
		case 65:
			trueKey = Key::Q;
			break;
		case 82:
			trueKey = Key::R;
			break;
		case 83:
			trueKey = Key::S;
			break;
		case 84:
			trueKey = Key::T;
			break;
		case 85:
			trueKey = Key::U;
			break;
		case 86:
			trueKey = Key::V;
			break;
		case 90:
			trueKey = Key::W;
			break;
		case 88:
			trueKey = Key::X;
			break;
		case 89:
			trueKey = Key::Y;
			break;
		case 87:
			trueKey = Key::Z;
			break;
		}
		
		if (action == GLFW_PRESS) {
			MessageBus::Send<Message::KeyPressed>(trueKey);
		} else if (action == GLFW_RELEASE) {
			MessageBus::Send<Message::KeyReleased>(trueKey);
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

		glfwSetFramebufferSizeCallback(static_cast<GLFWwindow*>(m_Window), FramebufferSizeCallback);
		glfwSetKeyCallback(static_cast<GLFWwindow*>(m_Window), KeyCallback);

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

	uint32_t Window::getWidth() const
	{
		int w, h;
		glfwGetFramebufferSize(static_cast<GLFWwindow*>(m_Window), &w, &h);
		return w;
	}

	uint32_t Window::getHeight() const
	{
		int w, h;
		glfwGetFramebufferSize(static_cast<GLFWwindow*>(m_Window), &w, &h);
		return h;
	}

	void Window::setTitle(std::string const& title)
	{
		glfwSetWindowTitle(static_cast<GLFWwindow*>(m_Window), title.c_str());
	}

	bool Window::shouldClose() const
	{
		return glfwWindowShouldClose(static_cast<GLFWwindow*>(m_Window));
	}

	void Window::swapBuffers()
	{
		glfwSwapBuffers(static_cast<GLFWwindow*>(m_Window));
	}

	void Window::PollEvents()
	{
		glfwPollEvents();
	}
}