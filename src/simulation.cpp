#include "simulation.h"

#include <ostream>
#include <stdexcept>

namespace sim {

Simulation::Simulation(int cols, int rows) : cols_(cols), rows_(rows) {
    if (cols <= 0 || rows <= 0) {
        throw std::invalid_argument("Simulation grid must be positive");
    }
}

void Simulation::add(std::shared_ptr<Shape2D> shape, const Vector2D& velocity) {
    if (!shape) {
        throw std::invalid_argument("Cannot add a null shape");
    }
    entities_.push_back(Entity{std::move(shape), velocity});
}

void Simulation::step(double dt) {
    for (auto& entity : entities_) {
        entity.shape->move(entity.velocity * dt);
    }
    bounceOffWalls();
    ++steps_;
}

void Simulation::bounceOffWalls() {
    for (auto& entity : entities_) {
        const Point2D& c = entity.shape->center();
        const double hw = entity.shape->halfWidth();
        const double hh = entity.shape->halfHeight();

        // Reflect only when moving into the wall, then clamp so a shape can
        // never tunnel outside the world.
        if (c.x - hw < 0.0 && entity.velocity.dx < 0.0) {
            entity.velocity = entity.velocity.reflectedX();
            entity.shape->move(Vector2D(hw - c.x, 0.0));
        } else if (c.x + hw > static_cast<double>(cols_) &&
                   entity.velocity.dx > 0.0) {
            entity.velocity = entity.velocity.reflectedX();
            entity.shape->move(
                Vector2D((static_cast<double>(cols_) - hw) - c.x, 0.0));
        }

        if (c.y - hh < 0.0 && entity.velocity.dy < 0.0) {
            entity.velocity = entity.velocity.reflectedY();
            entity.shape->move(Vector2D(0.0, hh - c.y));
        } else if (c.y + hh > static_cast<double>(rows_) &&
                   entity.velocity.dy > 0.0) {
            entity.velocity = entity.velocity.reflectedY();
            entity.shape->move(
                Vector2D(0.0, (static_cast<double>(rows_) - hh) - c.y));
        }
    }
}

std::vector<std::string> Simulation::render() const {
    // World y points up, screen rows run top to bottom: row r shows
    // world y = (rows - 1 - r). Cell centres sit at (c + 0.5, y + 0.5).
    std::vector<std::string> grid(rows_, std::string(cols_, '.'));

    for (int r = 0; r < rows_; ++r) {
        const double worldY =
            static_cast<double>(rows_ - 1 - r) + 0.5;
        for (int c = 0; c < cols_; ++c) {
            const Point2D p(static_cast<double>(c) + 0.5, worldY);
            for (const auto& entity : entities_) {
                if (entity.shape->contains(p)) {
                    grid[r][c] = entity.shape->brush();
                    break;
                }
            }
        }
    }
    return grid;
}

void Simulation::print(std::ostream& os) const {
    const std::vector<std::string> grid = render();

    const std::string top(static_cast<std::size_t>(cols_) + 2, '-');
    os << '+' << top << "+\n";
    for (const auto& row : grid) {
        os << '|' << row << "|\n";
    }
    os << '+' << top << "+\n";

    os << "step " << steps_ << " |";
    for (const auto& entity : entities_) {
        const Point2D& c = entity.shape->center();
        os << ' ' << entity.shape->name() << "@(" << c.x << "," << c.y << ")";
    }
    os << '\n';
}

}  // namespace sim
