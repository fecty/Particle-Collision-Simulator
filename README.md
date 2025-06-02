# SFML Project

This project contains example programs using [SFML 3.0.0](https://www.sfml-dev.org/) for graphics, window, and system functionality in C++.

## Requirements

- SFML 3.0.0 (static libraries)
- MinGW-w64 (for Windows, with g++)
- C++17 or newer

## Building

Use the provided VS Code tasks or run the following command from the `winlabs-mingw64` directory:

```sh
bin\g++ -std=c++17 -static -DSFML_STATIC ..\src\main.cpp -I../SFML-3.0.0/include -L../SFML-3.0.0/lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -o ../bin/main.exe
```

Or, for test files, replace `..\src\main.cpp` with the desired test file.

## Running

After building, run the executable from the `bin` directory:

```sh
.\bin\main.exe
```

Or use the "Run" task in VS Code.

## Project Structure

- `src/` - Main source files
- `tests/` - Test programs for SFML features
- `bin/` - Compiled executables
- `.vscode/` - VS Code configuration

## Notes

- Make sure SFML static libraries and headers are present in `SFML-3.0.0`.
- Update include/library paths as needed for your setup.
