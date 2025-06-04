# SFML Project

A collection of example and test programs using [SFML 3.0.0](https://www.sfml-dev.org/) for graphics, windowing, and system programming in C++. This project is set up for Windows with MinGW-w64 and includes VS Code integration.

## Features

- Multiple test programs demonstrating SFML features:
  - Window management and events
  - Graphics and animation (rotating shapes, bouncy ball)
  - Boids simulation (simple flocking)
  - Time and angle utilities
- Easy build and run tasks for Visual Studio Code
- Uses SFML static libraries

## Requirements

- [SFML 3.0.0](https://www.sfml-dev.org/) (static build, headers and libs in `SFML-3.0.0`)
- [MinGW-w64](https://www.mingw-w64.org/) (compiler in `winlabs-mingw64`)
- Visual Studio Code (recommended, for tasks and settings)
- C++17 or newer

## Project Structure

```
SFML project/
│
├── bin/                # Compiled executables
├── src/                # Main source files (entry: main.cpp)
├── tests/              # Test/demo programs (window, graphics, boids, etc.)
├── .vscode/            # VS Code tasks and settings
├── SFML-3.0.0/         # SFML include/ and lib/ (not tracked)
├── winlabs-mingw64/    # MinGW-w64 toolchain (not tracked)
├── README.md
├── .gitignore
```

## Building

Open the project in VS Code and use the built-in tasks:

- **Build**: Compiles the currently open file (main or any test) to `bin/`.
- **Run**: Runs the last built executable.
- **Build and Run**: Builds and then runs.

Or, from the command line (inside `winlabs-mingw64`):

```sh
bin\g++ -std=c++17 -static -DSFML_STATIC ..\src\main.cpp -I../SFML-3.0.0/include -L../SFML-3.0.0/lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -o ../bin/main.exe
```

Replace `..\src\main.cpp` with any test file, e.g., `..\tests\boid_sim_test.cpp`.

## Running

After building, run the executable from the `bin` directory:

```sh
.\bin\main.exe
```

Or use the "Run" task in VS Code.

## Notable Test Programs

- `src/main.cpp` - Minimal SFML window with a green circle.
- `tests/window_test.cpp` - Demonstrates window events and keyboard handling.
- `tests/rotating_shape_test.cpp` - Animated rotating rectangle and circle.
- `tests/bouncy_ball_test.cpp` - Bouncing ball with keyboard controls (requires `imgs/ball.png`).
- `tests/boid_sim_test.cpp` - Simple boids/flocking simulation with obstacle avoidance.
- `tests/time_test.cpp` - Demonstrates SFML time utilities.
- `tests/angles_test.cpp` - Demonstrates SFML angle utilities.

## Notes

- The `SFML-3.0.0` and `winlabs-mingw64` folders are not tracked by git (see `.gitignore`).
- Make sure to provide the required static SFML libraries and headers in `SFML-3.0.0`.
- For the bouncy ball test, place a `ball.png` image in an `imgs` folder at the project root.
- Update include/library paths in tasks or build commands if your folder structure differs.

---
**License:** See SFML's license for library usage. Example code here is public domain.
