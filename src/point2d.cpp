#include "point2d.h"

#include <cmath>

namespace sim {

double Point2D::distanceTo(const Point2D& other) const {
    const double dx = x - other.x;
    const double dy = y - other.y;
    return std::sqrt(dx * dx + dy * dy);
}

}  // namespace sim
