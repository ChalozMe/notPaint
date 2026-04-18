cmake_minimum_required(VERSION 3.10)
project(notPaint)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# CMake emits a warning if we don't set our FindOpenGL preference
if(POLICY CMP0072)
  cmake_policy(SET CMP0072 NEW)
endif()

find_package(OpenGL 3.3 REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

add_library(glad external/glad/src/glad.c)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL glfw glad)
target_include_directories(glad PUBLIC external/glad/include include)
