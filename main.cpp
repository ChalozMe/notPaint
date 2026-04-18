#include "Window.hpp"
#include <print>

static constexpr auto main_loop = [](GLFWwindow* window) {
  glClear(GL_COLOR_BUFFER_BIT);

  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
};

int main() {
  auto window = Window::create();
  if (!window)
    return std::println("{}", init_error_name(window.error())), -1;

  window->run(main_loop);
}
