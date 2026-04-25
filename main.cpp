#include "Drawable.hpp"
#include "Window.hpp"
#include "PixelGrid.hpp"
#include "Shapes/Ellipse.hpp"
#include <memory>
#include <print>

// this shouldn't be globals, we should probably encapsulate it in a class
static PixelGrid grid(800, 600);
static GLuint texture = 0;
static GLuint VAO = 0;
static GLuint VBO = 0;
static GLuint shader_program = 0;

static GLuint compile_shader(GLenum type, const char* src) {
  GLuint s = glCreateShader(type);
  glShaderSource(s, 1, &src, nullptr);
  glCompileShader(s);
  return s;
}

static GLuint create_program() {
  const char* vs = R"(
    #version 330 core
    layout (location = 0) in vec2 aPos;
    layout (location = 1) in vec2 aUV;
    out vec2 uv;
    void main() {
      uv = aUV;
      gl_Position = vec4(aPos, 0.0, 1.0);
    }
  )";

  const char* fs = R"(
    #version 330 core
    in vec2 uv;
    out vec4 FragColor;
    uniform sampler2D tex;
    void main() {
      FragColor = texture(tex, uv);
    }
  )";

  GLuint v = compile_shader(GL_VERTEX_SHADER, vs);
  GLuint f = compile_shader(GL_FRAGMENT_SHADER, fs);

  GLuint p = glCreateProgram();
  glAttachShader(p, v);
  glAttachShader(p, f);
  glLinkProgram(p);

  glDeleteShader(v);
  glDeleteShader(f);

  return p;
}

static void init_renderer() {
  // this does something with the gpul
  // i don't understand it, it works tho
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexImage2D(
    GL_TEXTURE_2D,
    0,
    GL_RGBA8,
    grid.width(),
    grid.height(),
    0,
    GL_RGBA,
    GL_UNSIGNED_BYTE,
    grid.data()
  );

  float quad[] = {
    -1.f, -1.f, 0.f, 0.f, 1.f, -1.f, 1.f, 0.f, 1.f,  1.f, 1.f, 1.f,
    -1.f, -1.f, 0.f, 0.f, 1.f, 1.f,  1.f, 1.f, -1.f, 1.f, 0.f, 1.f,
  };

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(
    1,
    2,
    GL_FLOAT,
    GL_FALSE,
    4 * sizeof(float),
    (void*)(2 * sizeof(float))
  );
  glEnableVertexAttribArray(1);

  shader_program = create_program();
}

int main() {
  std::vector<std::unique_ptr<Drawable>> drawables;

  PixelCoord off_center = {300, 400};
  Color red = {255, 0, 0, 255};
  drawables.push_back(
    std::make_unique<Ellipse>(off_center, Vector2{100.0f, 150.0f}, red)
  );

  PixelCoord center = {grid.width() / 2, grid.height() / 2};
  Color green = {0, 255, 0, 255};
  drawables.push_back(
    std::make_unique<Ellipse>(center, Vector2{50.0f, 50.0f}, green)
  );

  auto window = Window::create();
  if (!window)
    return std::println("{}", init_error_name(window.error())), -1;

  init_renderer();

  window->run([&drawables](GLFWwindow* window) {
    glClear(GL_COLOR_BUFFER_BIT);

    for (auto&& d : drawables)
      d->render(grid);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexSubImage2D(
      GL_TEXTURE_2D,
      0,
      0,
      0,
      grid.width(),
      grid.height(),
      GL_RGBA,
      GL_UNSIGNED_BYTE,
      grid.data()
    );

    glUseProgram(shader_program);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, true);
  });
}
