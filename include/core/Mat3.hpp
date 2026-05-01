#pragma once
#include <cmath>
#include "core/Vec2.hpp"



struct Mat3 {
    float m[3][3];

    static Mat3 identity() {
        return {{
            {1,0,0},
            {0,1,0},
            {0,0,1}
        }};
    }

    static Mat3 translation(float tx, float ty) {
        return {{
            {1,0,tx},
            {0,1,ty},
            {0,0,1}
        }};
    }

    static Mat3 scale(float sx, float sy) {
        return {{
            {sx,0,0},
            {0,sy,0},
            {0,0,1}
        }};
    }

    static Mat3 rotation(float a) {
        float c = std::cos(a);
        float s = std::sin(a);
        return {{
            {c,-s,0},
            {s, c,0},
            {0, 0,1}
        }};
    }

    Mat3 operator*(const Mat3& o) const {
        Mat3 r{};
        for (int i=0;i<3;i++)
            for (int j=0;j<3;j++)
                for (int k=0;k<3;k++)
                    r.m[i][j] += m[i][k]*o.m[k][j];
        return r;
    }

    Vec2 apply(Vec2 p) const {
        return {
            m[0][0]*p.x + m[0][1]*p.y + m[0][2],
            m[1][0]*p.x + m[1][1]*p.y + m[1][2]
        };
    }
};
