#pragma once

#include <string>

namespace Genesis
{
	class Window {
	public:
		Window(uint32_t width, uint32_t height, std::string const& title);
		~Window();

		void* getInternalPointer() const;

		uint32_t getWidth() const;
		uint32_t getHeight() const;

		void setTitle(std::string const& title);
		bool shouldClose() const;
		void swapBuffers();

		static void PollEvents();

	private:
		void* m_Window;
	};
}
