#ifndef CANVAS_MOUSE_HPP
#define CANVAS_MOUSE_HPP

#include "tool/Tool.hpp"
#include "selector/Selector.hpp"

template <tool::Tool T, char Key>
  requires(Key != 29) && (Key != 's')
struct Input {
  using Tool = T;
  static constexpr char key = Key;
};

template <class... Inputs>
class CanvasMouse {
public:
  using StaticTool = tool::StaticTool<typename Inputs::Tool...>;
  using Selector = selector::Selector<typename Inputs::Tool::Target...>;
  using StaticFigure = figure::StaticFigure<typename Inputs::Tool::Target...>;
  using Shape = shape::Shape<typename Inputs::Tool::Target...>;

private:
  std::variant<std::monostate, StaticTool, Selector> tool;

public:
  void draw(Renderer& renderer, const std::vector<Shape>& shapes) const {
    std::visit(
      [&]<class T>(const T& tool) {
        if constexpr (std::same_as<T, StaticTool>)
          tool.draw(renderer);
        else if constexpr (std::same_as<T, Selector>)
          tool.draw(renderer, shapes);
      },
      tool
    );
  }

  std::optional<StaticFigure>
  mouse(int button, int state, int x, int y, std::vector<Shape>& shapes) {
    return std::visit(
      [&]<class T>(T& tool) -> std::optional<StaticFigure> {
        if constexpr (std::same_as<T, StaticTool>)
          return tool.mouse(button, state, x, y);
        else if constexpr (std::same_as<T, Selector>)
          tool.mouse(button, state, x, y, shapes);
        return std::nullopt;
      },
      tool
    );
  }

public:
  void keyboard(unsigned char key) {
    auto dispatch_key =
      [this]<class First, class... Tail>(this auto&& rec, unsigned char key) {
        if (key == First::key)
          tool = typename First::Tool{};
        else if constexpr (sizeof...(Tail))
          rec.template operator()<Tail...>(key);
      };

    if (key == 27) // Escape key
      tool = std::monostate{};
    else if (key == 's')
      tool = Selector{};
    else
      dispatch_key.template operator()<Inputs...>(key);
  }
};

#endif
