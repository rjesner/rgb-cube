# RGB Cube

In this simple C++/CMake project, the goal is to render and rotate a 3D RGB cube using OpenGL inside a wxWidgets GUI. It demonstrates how to use these frameworks together to create useful software.

## Requisites

- Tested on Windows 10, may have to be adapted in other systems.

## Usage

Check the README.md of the folders inside the directory named 'third-party'.

Download and build the libraries inside a folder named 'cmake-build' for each of them. The CMakeLists.txt of the RGB Cube project should locate the dependecies automatically.

Then, just build the RGB Cube project inside its own 'cmake-build' folder:

```bash
$> cd rgb-cube
$> mkdir cmake-build
$> cd cmake-build
$> cmake ..
$> cmake -G "MinGW Makefiles" ..
```