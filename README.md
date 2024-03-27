# OSU Wanna Be

A simple implementation of the OSU rhythm game using the RayLib library and the C programming language. The game was created as part of an academic project.

## Build

This project uses the [CMake](https://cmake.org) tool. So it is necessary to install [CMake](https://cmake.org), depending on your operating system. You should also install the [Make](https://www.gnu.org/software/make/) tool for generating executable files

Use the following commands to generate build files in separate directory and build the project (You do not need to manually install RayLib before running the following commands. The `CMakeLists.txt` file included in the project will take care of that):

```bash
cmake -B build && cmake --build build
```

_Created using RayLib version 5.0, no external dependencies required._
