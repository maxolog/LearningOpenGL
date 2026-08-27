cmake_minimum_required(VERSION 3.20)

project(LearningOpenGL)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GLFW
add_subdirectory(glfw-3.4)

# GLAD
add_library(glad
    glad/src/glad.c
)

target_include_directories(glad PUBLIC
    glad/include
)

# Our program
add_executable(LearningOpenGL
    LearningOpenGL/LearningOpenGL.cpp
)

target_include_directories(LearningOpenGL PRIVATE
    glad/include
    glfw-3.4/include
)

target_link_libraries(LearningOpenGL
    glad
    glfw
)