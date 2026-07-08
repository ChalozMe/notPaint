#ifndef FIGURE_POLYGON_HPP
#define FIGURE_POLYGON_HPP

#include "Figure.hpp"
#include <algorithm>
#include <cmath>
#include <vector>
#include <ranges>

namespace figure {
struct Polygon {
  using Point = std::pair<std::size_t, std::size_t>;
  std::vector<Point> points;

  template <std::invocable<std::size_t, std::size_t> Visit>
  void visit_pixels(Visit&& visit) const {
    if (points.size() < 4)
      return;

    auto [min_x, max_x] = std::ranges::fold_left(
      points,
      std::pair{points[0].first, points[0].first},
      [](auto acc, Point p) {
        return std::pair{
          std::min(acc.first, p.first),
          std::max(acc.second, p.first)
        };
      }
    );

    auto [min_y, max_y] = std::ranges::fold_left(
      points,
      std::pair{points[0].second, points[0].second},
      [](auto acc, Point p) {
        return std::pair{
          std::min(acc.first, p.second),
          std::max(acc.second, p.second)
        };
      }
    );

    for (std::size_t y = min_y; y <= max_y; y++) {
      std::vector<double> crossings;

      for (auto [p1, p2] : std::views::pairwise(points)) {
        auto [x1, y1] = p1;
        auto [x2, y2] = p2;

        auto ly1 = static_cast<long long>(y1);
        auto ly2 = static_cast<long long>(y2);
        auto ly = static_cast<long long>(y);

        if ((ly1 > ly) != (ly2 > ly)) {
          double t =
            static_cast<double>(ly - ly1) / static_cast<double>(ly2 - ly1);
          double x = static_cast<double>(x1) +
            t * (static_cast<double>(x2) - static_cast<double>(x1));
          crossings.push_back(x);
        }
      }

      std::ranges::sort(crossings);

      for (auto span : std::views::chunk(crossings, 2)) {
        if (span.size() < 2)
          break;
        auto x_start = std::max<std::size_t>(min_x, std::ceil(span[0]));
        auto x_end = std::min<std::size_t>(max_x, std::floor(span[1]));
        for (std::size_t x = x_start; x <= x_end; x++)
          visit(x, y);
      }
    }
  }
};

static_assert(Figure<Polygon>, "A Polygon is a figure");
} // namespace figure

#endif
