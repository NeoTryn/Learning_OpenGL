cmake_minimum_required(VERSION 3.10.0)
project(Learning_OpenGL VERSION 0.1.0)

find_package(OpenGL REQUIRED)

add_executable(Learning_OpenGL 
                src/main.cpp
                src/glad.c
                src/Shader.hpp
                src/Shader.cpp
)

target_link_libraries(Learning_OpenGL 
                                glfw
                                OpenGL::GL
)