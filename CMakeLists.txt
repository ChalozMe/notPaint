cmake_minimum_required(VERSION 3.10)
project(notPaint)

# General config
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(POLICY CMP0072)
  cmake_policy(SET CMP0072 NEW)
endif()

# Dependency
find_package(OpenGL 3.3 REQUIRED)
find_package(glfw3 REQUIRED)

# GLAD (loader OpenGL)
add_library(glad external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

# src
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    src/*.cpp
)

add_executable(${PROJECT_NAME}
    main.cpp
    ${SRC_FILES}
)

# Includes
target_include_directories(${PROJECT_NAME}
    PRIVATE
    include
)

# Link
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    OpenGL::GL
    glfw
    glad
)

# Flags - compile
target_compile_options(${PROJECT_NAME}
    PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

# Copy shader to build
file(GLOB SHADERS CONFIGURE_DEPENDS shaders/*)

foreach(shader ${SHADERS})
    configure_file(${shader} ${CMAKE_BINARY_DIR} COPYONLY)
endforeach()
