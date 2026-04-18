#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <optional>
#include <type_traits>

class GlfwHandle {
  bool active;

  GlfwHandle() : active{true} {}

public:
  static std::optional<GlfwHandle> create() {
    return glfwInit() ? std::make_optional(GlfwHandle()) : std::nullopt;
  }

  GlfwHandle(GlfwHandle&& other) : active{other.active} {
    other.active = false;
  }

  GlfwHandle& operator=(GlfwHandle&& other) {
    if (this != &other) {
      active = other.active;
      other.active = false;
    }
    return *this;
  }

  GlfwHandle(const GlfwHandle&) = delete;
  GlfwHandle& operator=(const GlfwHandle&) = delete;

  ~GlfwHandle() {
    if (active)
      glfwTerminate();
  }
};
