# OOP-ISHA-MINIPROJECT — 2D Translation Simulation

A small C++17 object-oriented program that simulates **translation in 2D**:
shapes move through a world by repeatedly applying a translation vector
(`position += velocity * dt`) and bounce off the world's four walls.

## Concepts demonstrated

| OOP concept | Where it appears |
| --- | --- |
| Encapsulation | `Point2D`, `Vector2D` hide the arithmetic behind `translate()` / operators |
| Inheritance | `Rectangle` and `Circle` derive from the abstract `Shape2D` |
| Polymorphism | `area()`, `contains()`, `halfWidth()` are virtual; the simulation only sees `Shape2D` |
| Abstraction | `Simulation` works purely with shapes — it never knows their concrete types |
| Composition | A `Simulation` owns `Entity { shape, velocity }` pairs |
| RAII / smart pointers | Shapes are held by `std::shared_ptr<Shape2D>` |

## Layout

```
include/          public headers
  vector2d.h      translation vector (dx, dy), operators, reflection
  point2d.h       position + translate()
  shape2d.h       abstract base: area, contains, move, bounding box
  rectangle.h     axis-aligned rectangle
  circle.h        circle
  simulation.h    world: step(dt), wall bounce, ASCII rendering
src/              implementations + main.cpp
Makefile
```

## Build & run

```sh
make          # builds ./translation_sim (g++, C++17, -Wall -Wextra)
make run      # build + run the default demo
make web      # run the program and capture its frames to app/output.txt
make clean
```

```sh
./translation_sim              # 60 steps, print every 10th frame
./translation_sim 200 25       # 200 steps, print every 25th frame
./translation_sim --help
```

## View it in the browser

`app/index.html` is a single static page with two parts:

1. an interactive translation demo — enter `x`, `y`, `Tx`, `Ty`, hit
   **Apply Translation**, and see the original vs. translated rectangle with
   the formula `x′ = x + Tx`, `y′ = y + Ty`;
2. a replay of the program's real ASCII frames (step 10 → 200) with a
   **Stop** button to freeze on any frame.

```sh
make web                                  # regenerate app/output.txt
python3 -m http.server 3000 --directory app   # then open http://localhost:3000
```

## How it works

1. Each entity has a velocity (units/second). Every `step(dt)` the engine
   translates each shape by `velocity * dt`.
2. After translating, shapes that crossed a wall have that velocity component
   reflected and are clamped back inside the world — so nothing escapes.
3. `render()` rasterises the world to an ASCII grid: for every cell it asks
   each shape `contains(point)` (polymorphic) and stamps the shape's brush
   character.

Sample frame (real output at step 10):

```
+--------------------------------------------------------------+
|............................................................|
|............................................................|
|............................................................|
|............................................................|
|............OOOOOO..........................................|
|............OOOOOO..........................................|
|...........OOOOO########....................................|
|...........OOOOO########....................................|
|...........OOOOO########....................................|
|...........OOOOO########....................................|
|............OOOOOO..........................................|
|..............OO............................................|
|............................................................|
|............................................................|
|..............................==============................|
|..............................==============................|
|............................................................|
|............................................................|
+--------------------------------------------------------------+
step 10 | Box@(20,10) Ball@(15,10.4) Slab@(37,3)
```
