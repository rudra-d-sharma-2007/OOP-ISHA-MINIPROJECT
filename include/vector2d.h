#pragma once

namespace sim {

// A 2D translation vector: the "how far and in which direction" of a move.
class Vector2D {
public:
    double dx = 0.0;
    double dy = 0.0;

    Vector2D() = default;
    Vector2D(double dx_, double dy_) : dx(dx_), dy(dy_) {}

    Vector2D operator+(const Vector2D& other) const {
        return {dx + other.dx, dy + other.dy};
    }

    Vector2D operator*(double scale) const {
        return {dx * scale, dy * scale};
    }

    double magnitude() const;

    // Reflection helpers used when a shape bounces off a wall.
    Vector2D reflectedX() const { return {-dx, dy}; }
    Vector2D reflectedY() const { return {dx, -dy}; }
};

inline Vector2D operator*(double scale, const Vector2D& v) { return v * scale; }

}  // namespace sim
