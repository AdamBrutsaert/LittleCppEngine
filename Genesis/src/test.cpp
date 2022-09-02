#include "test.h"

#include <GLFW/glfw3.h>
#include <thread>

void test() {
  glfwInit();
  glfwCreateWindow(1280, 720, "title", nullptr, nullptr);
  std::this_thread::sleep_for(std::chrono::seconds(1));
  glfwTerminate();
}
