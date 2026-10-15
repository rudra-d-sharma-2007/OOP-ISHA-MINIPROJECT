#pragma once

#include <string>

#include "shape2d.h"

namespace sim {

class Rectangle : public Shape2D {
public:
    Rectangle(std::string name, char brush, Point2D center,
              double width, double height);

    double area() const override;
    bool contains(const Point2D& p) const override;
    std::string typeName() const override { return "Rectangle"; }
    double halfWidth() const override { return width_ / 2.0; }
    double halfHeight() const override { return height_ / 2.0; }

private:
    double width_;
    double height_;
};

}  // namespace sim
