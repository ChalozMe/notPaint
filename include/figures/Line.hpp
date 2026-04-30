#ifndef LINE_HPP
#define LINE_HPP

#include "Renderer.hpp"
#include "Color.hpp"

#include <cstdlib>

namespace figures {


//Bresenham's line algorithim  
inline void draw_line(
    Renderer& r,
    int x0, int y0,
    int x1, int y1,
    Color color
) {
    int dx = std::abs(x1 - x0);
    int dy = std::abs(y1 - y0);

    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;

    int err = dx - dy;

    while (true) {
        // limit out-of-bounds
        if (x0 >= 0 && y0 >= 0 &&
            x0 < (int)r.get_width() &&
            y0 < (int)r.get_height()) {
            r[x0, y0] = color;
        }

        if (x0 == x1 && y0 == y1)
            break;

        int e2 = 2 * err;

        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }

        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

}

#endif
