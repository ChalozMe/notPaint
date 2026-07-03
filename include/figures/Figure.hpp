#ifndef FIGURE_HPP
#define FIGURE_HPP

#include "Color.hpp"
#include <concepts>
#include <utility>
#include <variant>

namespace figures {
template <class F>
concept Figure = requires(const F& f) {
  requires std::copy_constructible<F>;
  {
    f.visit_pixels([](std::size_t, std::size_t, Color) {})
  } -> std::same_as<void>;
};

template <Figure... Fs>
class StaticFigure {
  using Variant = std::variant<Fs...>;
  Variant variant;

public:
  constexpr StaticFigure() = default;

  template <Figure F>
    requires(!std::same_as<std::remove_cvref_t<F>, StaticFigure>) &&
    (std::same_as<std::remove_cvref_t<F>, Fs> || ...)
  constexpr StaticFigure(F&& f) : variant(std::forward<F>(f)) {}

  template <Figure F, class... Args>
    requires std::constructible_from<F, Args...> &&
    (std::same_as<std::remove_cvref_t<F>, Fs> || ...)
  explicit constexpr StaticFigure(std::in_place_type_t<F>, Args&&... args) :
    variant(std::in_place_type<F>, std::forward<Args>(args)...) {}

  template <std::invocable<std::size_t, std::size_t, Color> Visit>
  void visit_pixels(Visit&& visit) const {
    std::visit(
      [&](auto&& f) { f.visit_pixels(std::forward<Visit>(visit)); },
      variant
    );
  }
};

} // namespace figures

#endif
