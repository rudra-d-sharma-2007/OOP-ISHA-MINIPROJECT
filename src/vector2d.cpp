#include "vector2d.h"

#include <cmath>

namespace sim {

double Vector2D::magnitude() const {
    return std::sqrt(dx * dx + dy * dy);
}

}  // namespace sim
