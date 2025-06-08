# SFML Project

This project showcases various features of the [SFML 3.0.0](https://www.sfml-dev.org/) library, including window management, graphics, system utilities, and more. It comprises a particle collision simulation and several test programs demonstrating specific SFML functionalities.

## Requirements

- SFML 3.0.0 (static libraries)
- [winlibs-mingw64](https://winlibs.com/) (for Windows, with g++)
- C++17 or newer
- VS Code (optional, for using provided tasks)

## Project Structure

- `src/` - Contains the main application source code:
  - `main.cpp`: A particle collision simulation.
- `tests/` - Includes various test programs demonstrating specific SFML features:
  - `window_test.cpp`: Demonstrates window creation, event handling, and basic window properties.
  - `time_test.cpp`: Shows how to use SFML's time and clock functionalities.
  - `angles_test.cpp`: Illustrates the use of SFML's angle types and literals.
  - `bouncy_ball_test.cpp`: A simple program demonstrating sprite movement, collision detection with window bounds, and keyboard input for controlling speed.
  - `boid_sim_test.cpp`: A boids simulation showcasing flocking behavior with obstacle avoidance.
  - `font_test.cpp`: Demonstrates how to load and display text using SFML's font and text classes.
  - `rotating_shape_test.cpp`: Demonstrates drawing and rotating shapes.
  - `barebone_template.cpp`: A barebone template for SFML projects.
- `bin/` - Where compiled executables are generated.
- `winlabs-mingw64/` - Contains the build environment configuration.
- `SFML-3.0.0/` - SFML library (headers and libraries). **Note:** This directory should contain the SFML library files. It is gitignored and not part of the repository.
- `.vscode/` - VS Code configuration files:
  - `tasks.json`: Defines build and run tasks for VS Code.
  - `settings.json`: Defines VS Code settings for the project, including file associations.
- `.gitignore`: Specifies intentionally untracked files that Git should ignore.
- `assets/`: Contains assets such as fonts and textures.

## Building

The project uses a `tasks.json` file for building within VS Code. Alternatively, you can build from the command line using `g++` provided by [winlibs-mingw64](https://winlibs.com/).

### Building with VS Code

1. Open the project in VS Code.
2. Use the "Build" task (Ctrl+Shift+B) to compile the currently open `.cpp` file. The output executable will be placed in the `bin/` directory.

### Building from the Command Line (MinGW-w64)

Navigate to the `winlabs-mingw64` directory in your terminal. Use the following command, adjusting the source file as needed:

```sh
bin\g++ -std=c++17 -static -DSFML_STATIC ..\src\main.cpp -I../SFML-3.0.0/include -L../SFML-3.0.0/lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -o ../bin/main.exe
```

For example, to build `tests/window_test.cpp`:

```sh
bin\g++ -std=c++17 -static -DSFML_STATIC ..\tests\window_test.cpp -I../SFML-3.0.0/include -L../SFML-3.0.0/lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -o ../bin/window_test.exe
```

## Running

### Running with VS Code

1. Use the "Run" task in VS Code to execute the compiled program. This will run the executable corresponding to the last built file.
2. The "Build and Run" task combines building and running in sequence.

### Running from the Command Line

Navigate to the project root directory and run the executable from the `bin/` directory:

```sh
.\bin\main.exe
```

Or, for test executables:

```sh
.\bin\window_test.exe
```

## Test Programs

The `tests/` directory contains several test programs that demonstrate different SFML features:

- **window_test.cpp**: Demonstrates creating and managing a window, handling events (close, key presses, resizing, text input, mouse movement), and setting window properties. It outputs window events and properties to the console.
- **time_test.cpp**: Shows how to use SFML's `sf::Clock` and `sf::Time` classes for measuring elapsed time.
- **angles_test.cpp**: Illustrates the usage of SFML's `sf::Angle` type and angle literals for working with angles in degrees and radians.
- **bouncy_ball_test.cpp**: Demonstrates sprite movement and collision detection. Use the arrow keys to adjust the ball's speed. Press `R` to reset the speed to zero and reposition the ball to the center. Press `Shift + R` to reset the position and speed.
- **boid_sim_test.cpp**: A boids simulation showcasing flocking behavior with obstacle avoidance.
  - Left-click to add a boid at the mouse position.
  - Right-click to move the obstacle to the mouse position.
  - Press `=` to add 10 boids.
  - Press `-` to remove 10 boids.
- **font_test.cpp**: Demonstrates how to load and display text using SFML's font and text classes.
- **rotating_shape_test.cpp**: Demonstrates drawing and rotating shapes.
- **barebone_template.cpp**: A barebone template for SFML projects.

## Main Application - Particle Collision Simulator

The `src/main.cpp` file contains a particle collision simulation. It creates a window and populates it with randomly colored particles that bounce around the screen.

## Resources and Assets

The `assets/` directory contains the following assets:

- `OpenSans.ttf`: A font file used for displaying text in the `font_test.cpp` and `bouncy_ball_test.cpp` files.
- `ball.png`: A texture used for the bouncy ball sprite in `bouncy_ball_test.cpp`.

## Notes

- Ensure that the SFML static libraries and headers are correctly placed in the `SFML-3.0.0` directory. This directory is excluded from version control.
- Adjust include and library paths in the build commands as necessary for your environment.
- The `tasks.json` file is configured to build and run the currently open file. Modify it to suit your specific needs.
- "winlabs-mingw64" and "SFML-3.0.0" are excluded files/folders.
- The `c_cpp_properties.json` file contains configurations for IntelliSense.  Ensure the `compilerPath` is correctly set to your MinGW-w64 g++ executable (e.g., `C:\\Code\\mingw64\\bin\\gcc.exe`).



