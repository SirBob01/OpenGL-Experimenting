cmake_minimum_required(VERSION 3.10)
project(.)

find_file(SDL2_INCLUDE_DIR NAME SDL.h HINTS SDL2)
find_library(SDL2_LIBRARY NAME SDL2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g -O")

# Renderer files
file(GLOB_RECURSE INCLUDE "../src/*.h")
file(GLOB_RECURSE SOURCES "../src/*.cpp" "../src/*.c")

# Make renderer a shared library
add_library(Renderer ${SOURCES} ${INCLUDE})
add_executable(main "../main.cpp")

# Compile with MinGW-w64
if(WIN32)
    target_link_libraries(main Renderer mingw32 SDL2main SDL2)
endif()

# Compile on Linux systems
if(UNIX OR MSVC)
    target_link_libraries(main Renderer SDL2)
endif()
