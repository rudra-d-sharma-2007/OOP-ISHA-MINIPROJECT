#include "circle.h"

#include <cmath>
#include <stdexcept>
#include <utility>

namespace sim {

namespace {
constexpr double kPi = 3.14159265358979323846;
}

Circle::Circle(std::string name, char brush, Point2D center, double radius)
    : Shape2D(std::move(name), brush, center), radius_(radius) {
    if (radius <= 0.0) {
        throw std::invalid_argument("Circle radius must be > 0");
    }
}

double Circle::area() const {
    return kPi * radius_ * radius_;
}

bool Circle::contains(const Point2D& p) const {
    return center_.distanceTo(p) <= radius_;
}

}  // namespace sim
