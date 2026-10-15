#pragma once

#include "vector2d.h"

namespace sim {

// A position in the 2D world. Applying a Vector2D translates the point.
class Point2D {
public:
    double x = 0.0;
    double y = 0.0;

    Point2D() = default;
    Point2D(double x_, double y_) : x(x_), y(y_) {}

    // The heart of the project: translate this point by a vector.
    void translate(const Vector2D& v) {
        x += v.dx;
        y += v.dy;
    }

    double distanceTo(const Point2D& other) const;
};

}  // namespace sim
