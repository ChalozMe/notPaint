#pragma once
#include "core/Mat3.hpp"

struct Transform2D {
    Mat3 mat = Mat3::identity();

    Transform2D& translate(float tx, float ty) {
        mat = Mat3::translation(tx, ty) * mat;
        return *this;
    }

    Transform2D& scale(float sx, float sy) {
        mat = Mat3::scale(sx, sy) * mat;
        return *this;
    }

    Transform2D& rotate(float angle) {
        mat = Mat3::rotation(angle) * mat;
        return *this;
    }

    Vec2 apply(Vec2 p) const {
        return mat.apply(p);
    }
};
