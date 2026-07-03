#ifndef FIGURE_HPP
#define FIGURE_HPP

#include <concepts>
#include <utility>
#include <variant>
#include "Renderer.hpp"

namespace figures {
template <class F>
concept Figure = requires(const F& f, Renderer& r) {
  requires std::copy_constructible<F>;
  { f.draw(r) } -> std::same_as<void>;
};

// Type erased class, value semantics, non-nullable
template <Figure... Fs>
class StaticFigure {
  using Variant = std::variant<Fs...>;
  Variant v;

public:
  constexpr StaticFigure() = default;

  template <Figure F>
    requires(!std::same_as<std::remove_cvref_t<F>, StaticFigure>) &&
    (std::same_as<std::remove_cvref_t<F>, Fs> || ...)
  constexpr StaticFigure(F&& f) : v(std::forward<F>(f)) {}

  template <Figure F, class... Args>
    requires std::constructible_from<F, Args...> &&
    (std::same_as<std::remove_cvref_t<F>, Fs> || ...)
  explicit constexpr StaticFigure(std::in_place_type_t<F>, Args&&... args) :
    v(std::in_place_type<F>, std::forward<Args>(args)...) {}

  void draw(Renderer& r) const {
    std::visit([&r](auto&& f) { f.draw(r); }, v);
  }
};

} // namespace figures

#endif
