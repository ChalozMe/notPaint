#include "Window.hpp"
#include "graphics/Renderer.hpp"
#include "graphics/Shader.hpp"

#include <print>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main() {
    auto window = Window::create();
    if (!window)
        return std::println("{}", init_error_name(window.error())), -1;

    // IMPORTANTE: a este punto ya debe existir el contexto OpenGL
    // (asumimos que Window::create() + run() inicializan GLAD correctamente)

    Renderer renderer;
    Shader shader("basic.vert", "basic.frag");

    auto main_loop = [&](GLFWwindow* w) {
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        renderer.drawPoint(0.0f, 0.0f);

        if (glfwGetKey(w, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(w, true);
    };

    window->run(main_loop);
}
