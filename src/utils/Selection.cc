#include "Selection.h"

#include <cmath>

float distance(Vec2 a, Vec2 b)
{
    float dx = a.x - b.x;
    float dy = a.y - b.y;

    return sqrt(dx*dx + dy*dy);
}

float pointSegmentDistance(Vec2 p, Vec2 a, Vec2 b)
{
    float dx = b.x - a.x;
    float dy = b.y - a.y;

    float len2 = dx*dx + dy*dy;

    if(len2 == 0)
        return distance(p, a);

    float t = ((p.x - a.x)*dx + (p.y - a.y)*dy) / len2;

    if(t < 0)
        t = 0;

    if(t > 1)
        t = 1;

    float px = a.x + t*dx;
    float py = a.y + t*dy;

    return distance(p, {px, py});
}
