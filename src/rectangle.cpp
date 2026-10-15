#include "rectangle.h"

#include <cmath>
#include <stdexcept>
#include <utility>

namespace sim {

Rectangle::Rectangle(std::string name, char brush, Point2D center,
                     double width, double height)
    : Shape2D(std::move(name), brush, center),
      width_(width),
      height_(height) {
    if (width <= 0.0 || height <= 0.0) {
        throw std::invalid_argument("Rectangle width and height must be > 0");
    }
}

double Rectangle::area() const {
    return width_ * height_;
}

bool Rectangle::contains(const Point2D& p) const {
    return std::abs(p.x - center_.x) <= width_ / 2.0 &&
           std::abs(p.y - center_.y) <= height_ / 2.0;
}

}  // namespace sim
