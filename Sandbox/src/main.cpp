#include <Window.h>

using namespace Genesis;

int main() {
	
	Window window{ 1280, 720, "Ticks : Unknown " };

	while (!window.shouldClose())
	{
		window.swapBuffers();
		Window::PollEvents();
	}

	return 0;
}
