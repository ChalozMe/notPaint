#pragma once
#include "graphics/Renderer.hpp"
#include "graphics/Color.hpp"
#include "core/Vec2.hpp"
#include "transform/Transform2D.hpp"
#include <cstdlib>

namespace figures {

inline void draw_line(
    Renderer& r,
    Vec2 p0,
    Vec2 p1,
    Color color,
    const Transform2D* t = nullptr
) {
    if (t) {
        p0 = t->apply(p0);
        p1 = t->apply(p1);
    }

    int x0 = (int)p0.x, y0 = (int)p0.y;
    int x1 = (int)p1.x, y1 = (int)p1.y;

    int dx = std::abs(x1 - x0), dy = std::abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        if (x0>=0 && y0>=0 && x0<(int)r.get_width() && y0<(int)r.get_height())
            r[x0, y0] = color;

        if (x0==x1 && y0==y1) break;

        int e2 = 2*err;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 <  dx) { err += dx; y0 += sy; }
    }
}

}
