#pragma once

#include <string>

#include "shape2d.h"

namespace sim {

class Circle : public Shape2D {
public:
    Circle(std::string name, char brush, Point2D center, double radius);

    double area() const override;
    bool contains(const Point2D& p) const override;
    std::string typeName() const override { return "Circle"; }
    double halfWidth() const override { return radius_; }
    double halfHeight() const override { return radius_; }

private:
    double radius_;
};

}  // namespace sim
