#pragma once

#include <string>

namespace Genesis
{
	class Window {
	public:
		Window(uint32_t width, uint32_t height, std::string const& title);
		~Window();

		bool shouldClose() const;
		void swapBuffers() const;

		static void PollEvents();

	private:
		void* m_Window;
	};
}