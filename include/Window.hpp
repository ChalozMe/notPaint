#include <expected>
#include <memory>
#include <string_view>
#include <utility>
#include "GlfwHanfle.hpp"

enum class WindowInitError {
  GlfwError,
  WindowError,
  GladError,
};

constexpr std::string_view init_error_name(WindowInitError e) {
  switch (e) {
    case WindowInitError::GlfwError:
      return "Failed to init GLFW";
    case WindowInitError::WindowError:
      return "Failed to init window";
    case WindowInitError::GladError:
      return "Failed to init GLAD";
  }
  std::unreachable();
}

class Window {
  using WindowDeleter = decltype([](GLFWwindow* window) {
    if (window)
      glfwDestroyWindow(window);
  });

  GlfwHandle handle;
  std::unique_ptr<GLFWwindow, WindowDeleter> window;

  Window(GlfwHandle h, GLFWwindow* w) : handle{std::move(h)}, window{w} {}

public:
  static std::expected<Window, WindowInitError> from_handle(GlfwHandle handle) {
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);
    if (!window)
      return std::unexpected(WindowInitError::WindowError);

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
      return std::unexpected(WindowInitError::GladError);

    return Window{std::move(handle), window};
  }

  static std::expected<Window, WindowInitError> create() {
    auto handle = GlfwHandle::create();
    return handle ? from_handle(std::move(*handle))
                  : std::unexpected(WindowInitError::GlfwError);
  }

  Window(Window&&) = default;
  Window& operator=(Window&&) = default;
  Window(const Window&) = delete;
  Window& operator=(const Window&) = delete;

  template <std::invocable<GLFWwindow*> F>
  void run(F&& runnable) {
    while (!glfwWindowShouldClose(window.get())) {
      runnable(window.get());
      glfwSwapBuffers(window.get());
      glfwPollEvents();
    }
  }
};
