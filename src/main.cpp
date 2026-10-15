#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>

#include "circle.h"
#include "rectangle.h"
#include "simulation.h"

namespace {

void printUsage(const char* prog) {
    std::cout << "2D Translation Simulation\n"
              << "Usage: " << prog << " [steps] [print_every]\n"
              << "  steps        total simulation steps   (default 60)\n"
              << "  print_every  print a frame every N steps (default 10)\n";
}

}  // namespace

int main(int argc, char** argv) {
    if (argc > 1 && (std::string(argv[1]) == "-h" ||
                     std::string(argv[1]) == "--help")) {
        printUsage(argv[0]);
        return 0;
    }
    if (argc > 3) {
        printUsage(argv[0]);
        return 1;
    }

    const int steps = argc > 1 ? std::atoi(argv[1]) : 60;
    const int printEvery = argc > 2 ? std::atoi(argv[2]) : 10;
    if (steps <= 0 || printEvery <= 0) {
        std::cerr << "steps and print_every must be positive integers\n";
        return 1;
    }

    try {
        sim::Simulation world(/*cols=*/60, /*rows=*/18);

        world.add(std::make_shared<sim::Rectangle>("Box", '#',
                                                   sim::Point2D(8, 4), 8, 4),
                  sim::Vector2D(12.0, 6.0));
        world.add(std::make_shared<sim::Circle>("Ball", 'O',
                                                sim::Point2D(30, 9), 4),
                  sim::Vector2D(-15.0, 9.0));
        world.add(std::make_shared<sim::Rectangle>("Slab", '=',
                                                   sim::Point2D(50, 14), 14, 2),
                  sim::Vector2D(20.0, -11.0));

        std::cout << "2D translation simulation: 60x18 world, dt = 0.1 s\n"
                  << "Shapes translate by v*dt each step and bounce off "
                     "walls.\n\n";

        const double dt = 0.1;
        for (int i = 1; i <= steps; ++i) {
            world.step(dt);
            if (i % printEvery == 0 || i == steps) {
                world.print(std::cout);
                std::cout << '\n';
            }
        }

        std::cout << "Final state:\n";
        for (const auto& entity : world.entities()) {
            const sim::Point2D& c = entity.shape->center();
            std::cout << "  " << entity.shape->name() << " ("
                      << entity.shape->typeName() << ") center=(" << c.x
                      << ", " << c.y << ") area=" << entity.shape->area()
                      << " velocity=(" << entity.velocity.dx << ", "
                      << entity.velocity.dy << ")\n";
        }
        std::cout << "Completed " << world.steps() << " steps.\n";
    } catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}
