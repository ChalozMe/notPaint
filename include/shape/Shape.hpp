#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "figures/Figure.hpp"
#include "Renderer.hpp"

namespace shape {
template <figures::Figure... Fs>
struct Shape {
  figures::StaticFigure<Fs...> figure;
  Color color;

  bool is_clicked(std::size_t x, std::size_t y) const {
    bool is_clicked = false;

    figure.visit_pixels([&](std::size_t _x, std::size_t _y) {
      is_clicked = is_clicked || (x == _x && y == _y);
    });

    return is_clicked;
  }

  void draw(Renderer& r) const {
    figure.visit_pixels([&](std::size_t x, std::size_t y) {
      if (x < r.get_width() && y < r.get_height())
        r[x, y] = color;
    });
  }
};

namespace {
  template <class Sf>
  struct FromStaticFigureImpl;

  template <class... Fs>
  struct FromStaticFigureImpl<figures::StaticFigure<Fs...>> {
    using t = Shape<Fs...>;
  };
} // namespace

template <class Sf>
using FromStaticFigure = FromStaticFigureImpl<Sf>::t;
} // namespace shape

#endif
