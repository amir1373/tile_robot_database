# Tile Robot Database

C++/CMake support repository for the tile robot UI/database workflow.

## What This Repository Contains

- `src/` - C++ source files.
- `include/` - headers.
- `CMakeLists.txt` - CMake build configuration.
- `builder.bash` - build helper script.
- `docker-compose.yml` - containerized service configuration.
- `.github/workflows/cmake.yml` - CMake CI workflow.
- `.gitmodules` - submodule references, if used by the project.

## Build

```bash
cmake -S . -B build
cmake --build build
```

or use the project helper script if it matches your environment:

```bash
bash builder.bash
```

## Notes

Document the expected database/service role, ports, schemas, and UI integration path as this repository is cleaned up.