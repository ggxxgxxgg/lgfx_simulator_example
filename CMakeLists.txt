cmake_minimum_required(VERSION 3.20)

project(lgfx_simulator_example)

find_package(SDL2 REQUIRED SDL2)
include_directories(PUBLIC ${SDL2_INCLUDE_DIRS})

add_subdirectory(dependencies/lgfx_simulator)
add_subdirectory(dependencies/LovyanGFX)
