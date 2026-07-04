#ifndef TOOL_HPP
#define TOOL_HPP

#include "Renderer.hpp"
#include "figures/Figure.hpp"
#include <optional>

namespace tools {

template <class T>
concept Tool = requires(T& t, Renderer& r) {
  typename T::Target;
  requires figures::Figure<typename T::Target>;
  { t.mouse(0, 0, 0, 0) } -> std::same_as<std::optional<typename T::Target>>;
  { std::as_const(t).draw(r) } -> std::same_as<void>;
};

template <Tool... Ts>
class StaticTool {
  using Variant = std::variant<Ts...>;
  Variant variant;

public:
  constexpr StaticTool() = default;

  template <Tool T>
    requires(!std::same_as<std::remove_cvref_t<T>, StaticTool>) &&
    (std::same_as<std::remove_cvref_t<T>, Ts> || ...)
  constexpr StaticTool(T&& t) : variant(std::forward<T>(t)) {}

  template <Tool T, class... Args>
    requires std::constructible_from<T, Args...> &&
    (std::same_as<std::remove_cvref_t<T>, Ts> || ...)
  explicit constexpr StaticTool(std::in_place_type_t<T>, Args&&... args) :
    variant(std::in_place_type<T>, std::forward<Args>(args)...) {}

  using StaticFigure = figures::StaticFigure<typename Ts::Target...>;

  std::optional<StaticFigure> mouse(int button, int state, int x, int y) {
    return std::visit(
      [&](auto&& t) -> std::optional<StaticFigure> {
        return t.mouse(button, state, x, y);
      },
      variant
    );
  }

  void draw(Renderer& r) const {
    std::visit([&](auto&& t) { t.draw(r); }, variant);
  }
};

} // namespace tools

#endif
