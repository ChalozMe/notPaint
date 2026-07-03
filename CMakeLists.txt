cmake_minimum_required(VERSION 3.11.0)
project(notPaint)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(POLICY CMP0072)
  cmake_policy(SET CMP0072 NEW)
endif()

find_package(OpenGL 2.1 REQUIRED)
find_package(GLUT REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL OpenGL::GLU GLUT::GLUT)

