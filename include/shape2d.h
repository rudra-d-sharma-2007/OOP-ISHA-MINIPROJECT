#pragma once

#include <string>
#include <utility>

#include "point2d.h"
#include "vector2d.h"

namespace sim {

// Abstract base class for everything that can be translated in the world.
class Shape2D {
public:
    Shape2D(std::string name, char brush, Point2D center)
        : name_(std::move(name)), brush_(brush), center_(center) {}

    virtual ~Shape2D();

    virtual double area() const = 0;
    virtual bool contains(const Point2D& p) const = 0;
    virtual std::string typeName() const = 0;

    // Half extents of the axis-aligned bounding box, used for wall bounces.
    virtual double halfWidth() const = 0;
    virtual double halfHeight() const = 0;

    // Translation entry point: every shape moves by the same rule.
    void move(const Vector2D& v) { center_.translate(v); }

    const Point2D& center() const { return center_; }
    char brush() const { return brush_; }
    const std::string& name() const { return name_; }

protected:
    std::string name_;
    char brush_;
    Point2D center_;
};

}  // namespace sim
