#pragma once

#include <iosfwd>
#include <memory>
#include <string>
#include <vector>

#include "shape2d.h"
#include "vector2d.h"

namespace sim {

// The world: a grid of cols x rows world units in which shapes translate
// at constant velocity and bounce off the four walls.
class Simulation {
public:
    struct Entity {
        std::shared_ptr<Shape2D> shape;
        Vector2D velocity;
    };

    Simulation(int cols, int rows);

    void add(std::shared_ptr<Shape2D> shape, const Vector2D& velocity);

    // Advance the whole world by dt seconds (velocity is in units/second).
    void step(double dt);

    int steps() const { return steps_; }
    int cols() const { return cols_; }
    int rows() const { return rows_; }
    const std::vector<Entity>& entities() const { return entities_; }

    // ASCII frame of the world interior, one string per row (top row first).
    std::vector<std::string> render() const;

    // Full bordered frame plus a line of per-shape status.
    void print(std::ostream& os) const;

private:
    void bounceOffWalls();

    int cols_;
    int rows_;
    int steps_ = 0;
    std::vector<Entity> entities_;
};

}  // namespace sim
