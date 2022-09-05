#include "Precompiled.h"
#include "Core/Window.h"

#include "MessageBus/MessageBus.h"
#include "Core/Input.h"

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
		switch (action)
		{
		case GLFW_PRESS:
			MessageBus::Send<Message::KeyPressed>(MapIntToKey(key));
			break;
		case GLFW_RELEASE:
			MessageBus::Send<Message::KeyReleased>(MapIntToKey(key));
			break;
		case GLFW_REPEAT:
			MessageBus::Send<Message::KeyRepeat>(MapIntToKey(key));
			break;
		}
	}

	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		if (action == GLFW_PRESS) {
			MessageBus::Send<Message::MouseButtonPressed>(MapIntToMouseButton(button));
		} else {
			MessageBus::Send<Message::MouseButtonReleased>(MapIntToMouseButton(button));
		}
	}

	static void MousePositionCallback(GLFWwindow* window, double xpos, double ypos)
	{
		MessageBus::Send<Message::MouseMove>(static_cast<int32_t>(xpos), static_cast<int32_t>(ypos));
	}

	void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		MessageBus::Send<Message::MouseScroll>(xoffset, yoffset);
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
		glfwSetMouseButtonCallback(static_cast<GLFWwindow*>(m_Window), MouseButtonCallback);
		glfwSetCursorPosCallback(static_cast<GLFWwindow*>(m_Window), MousePositionCallback);
		glfwSetScrollCallback(static_cast<GLFWwindow*>(m_Window), MouseScrollCallback);

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

	void* Window::getInternalPointer() const
	{
		return m_Window;
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
