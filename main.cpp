#include "Window.hpp"
#include "graphics/Shader.hpp"

#include <print>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main() {
    auto window = Window::create();
    if (!window)
        return std::println("{}", init_error_name(window.error())), -1;

    Shader shader("shaders/basic.vert", "shaders/basic.frag");

    // --- Setup VAO/VBO ---
    float vertices[] = {
        0.0f, 0.0f, 0.0f // punto en el centro
    };

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Opcional pero útil
    glPointSize(10.0f);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    auto main_loop = [&](GLFWwindow* w) {
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_POINTS, 0, 1);

        if (glfwGetKey(w, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(w, true);
    };

    window->run(main_loop);
}
