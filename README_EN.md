# Way Home

[Русский](README.md) | **English**

![C++](https://img.shields.io/badge/C%2B%2B-SFML-00599C?logo=cplusplus)
![SFML](https://img.shields.io/badge/SFML-2.5.1-8CC445)
![Genre](https://img.shields.io/badge/genre-space%20arcade-191970)

A space arcade game about returning a ship to Earth. Travel through several
consecutive stages, avoid meteorites, space debris, and other ships, collect
fuel, and follow your progress on the radar.

## Gameplay

- movement consumes fuel;
- fuel cans restore different amounts of fuel;
- colliding with a dangerous object causes defeat;
- object speed and difficulty increase as the journey continues;
- the route contains meteorite, debris, and spaceship phases;
- the top-panel indicator shows the remaining distance to Earth;
- a final screen appears after every stage is completed.

## Controls

| Keys | Action |
|---|---|
| `WASD` or `Num 8/4/5/6` | move the ship |
| `Pause` | pause |
| `M` | toggle music |
| `R` | restart the journey |
| `End` | quit |

## Architecture

| File | Purpose |
|---|---|
| `main.cpp` | main loop, route stages, UI, and rules |
| `ExternalWorld.*` | obstacles, bonuses, speed, and object respawning |
| `GameLibrary.*` | animation, text, and movement helpers |
| `Image` | ship, space, Earth, obstacles, and interface assets |
| `Music` | music and sound effects |
| `Font` | interface font |

## Building

The project targets Windows, Visual Studio 2022, and SFML 2.5.1 x64.

1. Install an SFML build matching your MSVC version and x64 architecture.
2. Open `Простая игра SMFL.sln`.
3. Replace the `SFML/include` and `SFML/lib` paths in the project properties.
4. Select `Debug x64` or `Release x64` and build the solution.
5. Run with the repository root as the working directory so the relative paths
   can access `Image`, `Music`, and `Font`.

> The repository does not currently include a CMake configuration. SFML DLLs
> are included, but they must match the selected configuration and compiler.

## Status

Playable educational prototype. Useful next steps include moving route logic
to a state machine, storing objects in `std::vector`, adding a settings screen,
and making all movement independent of FPS.
