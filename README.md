# LearningOpenGL

# LearnOpenGL Project

This repository contains my code and progress while working on the computer graphics project

It is a modern OpenGL application written in C++ using CMake as the build system.

## 🛠️ Technologies Used

- **C++**
- **OpenGL** (Graphics API)
- **GLFW** (Window creation and input handling)
- **GLAD** (OpenGL function pointer loader)
- **CMake** (Build system)

## 🐧 Linux (Ubuntu/Debian) Setup

To build this project on Linux, you need to install a C++ compiler, CMake, and the required display server development packages (for both Wayland and X11).

Open your terminal and run:

````bash
sudo apt update
sudo apt install build-essential cmake libwayland-dev wayland-protocols libxkbcommon-dev xorg-dev



### Building the Project

After cloning or downloading this repository, you need to generate the build files before running the program. Open a terminal in the root directory of the project and run:

```bash
cmake -S . -B build
cmake --build build
````

This will create the `build` directory, configure the project using CMake, and compile the executable. Once the build is complete, the executable will be located inside the generated `build` directory. You can then run the program from there.

If you make changes to the source code, simply run `cmake --build build` again to rebuild the project.

# Running the program

1. Make sure you are in the main project file LearningOpenGl which contains all the folders
2. If you are on Linux --- ./build/LearningOpenGL
3. If you are on windows --- .\build\LearnOpenGL
