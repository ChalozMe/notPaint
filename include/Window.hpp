#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <expected>
#include <memory>
#include <string_view>
#include <utility>
#include "GlfwHandle.hpp"
#include "Renderer.hpp"

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
  using UniqueWindow = std::unique_ptr<GLFWwindow, WindowDeleter>;

  Renderer renderer;
  GlfwHandle handle;
  UniqueWindow window;

  Window(Renderer&& renderer, GlfwHandle h, UniqueWindow w) :
    renderer{std::move(renderer)},
    handle{std::move(h)},
    window{std::move(w)} {}

public:
  static std::expected<Window, WindowInitError> from_handle(GlfwHandle handle) {
    const auto width = 800;
    const auto height = 800;
    UniqueWindow window(
      glfwCreateWindow(width, height, "OpenGL", nullptr, nullptr)
    );
    if (!window)
      return std::unexpected(WindowInitError::WindowError);

    glfwMakeContextCurrent(window.get());

    // if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    // return std::unexpected(WindowInitError::GladError);

    return Window{
      Renderer(width, height),
      std::move(handle),
      std::move(window)
    };
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

  template <std::invocable<Renderer&, GLFWwindow*> F>
  void run(F&& runnable) {
    while (!glfwWindowShouldClose(window.get())) {
      runnable(renderer, window.get());

      renderer.send_to_gpu();
      glfwSwapBuffers(window.get());
      glfwPollEvents();
    }
  }
};

#endif
